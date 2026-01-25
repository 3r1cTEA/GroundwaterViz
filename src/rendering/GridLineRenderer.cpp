#include "GridLineRenderer.h"

#include <QMatrix4x4>
#include <QVector3D>

GridLineRenderer::GridLineRenderer()
{

}

GridLineRenderer::~GridLineRenderer()
{
    vao.destroy();
    vbo.destroy();
}

void GridLineRenderer::initialize()
{
    initializeOpenGLFunctions();

    const char *vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        uniform mat4 mvp;
        void main()
        {
            gl_Position = mvp * vec4(position, 1.0);
        })";

    const char *fragmentShader = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.0, 0.0, 1.0, 1.0);
        })";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();


    vao.create();
    vbo.create();

    buildGridLines();
}

void GridLineRenderer::render(const Camera &camera)
{
    program.bind();



        QMatrix4x4 mvp = camera.projectionMatrix() * camera.viewMatrix();
        program.setUniformValue("mvp", mvp);

        vao.bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
        vao.release();

        program.release();
}

void GridLineRenderer::buildGridLines()
{

        std::vector<QVector3D> vertices;

        float width  = nx * dx;
        float depth  = ny * dy;
        float height = nz * dz;

        // X-direction lines
        for (int j = 0; j <= ny; ++j)
        {
            for (int k = 0; k <= nz; ++k)
            {
                float y = j * dy;
                float z = k * dz;

                vertices.emplace_back(0.0f, y, z);
                vertices.emplace_back(width, y, z);
            }
        }

        // Y-direction lines
        for (int i = 0; i <= nx; ++i)
        {
            for (int k = 0; k <= nz; ++k)
            {
                float x = i * dx;
                float z = k * dz;

                vertices.emplace_back(x, 0.0f, z);
                vertices.emplace_back(x, depth, z);
            }
        }

        // Z-direction lines
        for (int i = 0; i <= nx; ++i)
        {
            for (int j = 0; j <= ny; ++j)
            {
                float x = i * dx;
                float y = j * dy;

                vertices.emplace_back(x, y, 0.0f);
                vertices.emplace_back(x, y, height);
            }
        }

        vertexCount = static_cast<int>(vertices.size());

        vao.bind();
        vbo.bind();
        vbo.allocate(vertices.data(), vertexCount * sizeof(QVector3D));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(QVector3D), nullptr);

        vao.release();
        vbo.release();


}
