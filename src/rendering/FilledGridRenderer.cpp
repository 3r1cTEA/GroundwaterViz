#include "FilledGridRenderer.h"


#include <QVector3D>
#include <vector>



FilledGridRenderer::FilledGridRenderer(const GridMesh &mesh):m_mesh{mesh}
{

}

FilledGridRenderer::~FilledGridRenderer()
{
vao.destroy();
vbo.destroy();
ebo.destroy();
}

void FilledGridRenderer::initialize()
{
    initializeOpenGLFunctions();

    const char *vertexShader = R"(#version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec3 aNormal;

            uniform mat4 uView;
            uniform mat4 uProj;

            out vec3 vNormal;
            out vec3 vWorldPos;

            void main()
            {
                vNormal = aNormal;
                vWorldPos = aPosition;

                gl_Position = uProj * uView * vec4(aPosition, 1.0);
            }
            )";

    const char *fragmentShader = R"(#version 330 core

            in vec3 vNormal;
            in vec3 vWorldPos;

            out vec4 FragColor;

            uniform vec3 uLightDir = normalize(vec3(0.5, 1.0, 0.3));
            uniform vec3 uColor    = vec3(0.7, 0.75, 0.8);

            void main()
            {
                vec3 N = normalize(vNormal);
                float diff = max(dot(N, -uLightDir), 0.0);

                vec3 ambient = 0.25 * uColor;
                vec3 diffuse = diff * uColor;

                FragColor = vec4(ambient + diffuse, 1.0);
            }
            )";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();


    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(m_mesh.vertices().data(),
                 static_cast<int>(m_mesh.vertices().size() * sizeof(GridMesh::Vertex)));

    ebo.create();
    ebo.bind();
    ebo.allocate(m_mesh.indices().data(),
                 static_cast<int>(m_mesh.indices().size() * sizeof(unsigned int)));

    indexCount = static_cast<int>(m_mesh.indices().size());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        sizeof(GridMesh::Vertex),
        reinterpret_cast<void*>(offsetof(GridMesh::Vertex, position))
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        sizeof(GridMesh::Vertex),
        reinterpret_cast<void*>(offsetof(GridMesh::Vertex, normal))
    );

   // program.release();
    vao.release();

    qDebug() << "FilledGridRenderer initialized";


}

void FilledGridRenderer::render(const Camera &camera)
{
    if (!vao.isCreated() || indexCount == 0)
            return;

        program.bind();
        program.setUniformValue("uView", camera.viewMatrix());
        program.setUniformValue("uProj", camera.projectionMatrix());

        vao.bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        vao.release();

        program.release();

}


