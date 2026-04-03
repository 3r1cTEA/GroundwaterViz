#include "FilledGridRenderer.h"



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
    qDebug() << "FilledGridRenderer initialized\n";
    initializeOpenGLFunctions();

    program.removeAllShaders();

    const char *vertexShader = R"(#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in float scalar;

out vec3 vNormal;


uniform mat4 MVP;
uniform mat4 model;

void main()
{
    gl_Position = MVP * vec4(position,1.0);
    vNormal = mat3(model) * normal;

}
            )";

    const char *fragmentShader = R"(#version 330 core

            in vec3 vNormal;

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



    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GridMesh::Vertex),
        reinterpret_cast<void*>(0)
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GridMesh::Vertex),
        reinterpret_cast<void*>(offsetof(GridMesh::Vertex, normal))
    );

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2,
        1,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GridMesh::Vertex),
        reinterpret_cast<void*>(offsetof(GridMesh::Vertex, scalar))
    );

    glEnableVertexAttribArray(2);

   // program.release();
    vao.release();

    qDebug() << "FilledGridRenderer initialized";


}

void FilledGridRenderer::render(const Camera &camera)
{
    if (!vao.isCreated() || indexCount == 0)
            return;

    program.bind();

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 MVP = camera.projectionMatrix() * camera.viewMatrix() * model;
    program.setUniformValue("MVP", MVP);
    program.setUniformValue("model", model);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    vao.release();
    program.release();

}


