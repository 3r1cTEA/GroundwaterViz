#include "GridRenderer.h"

GridRenderer::GridRenderer()
{

}

GridRenderer::~GridRenderer()
{
    vao.destroy();
    vbo.destroy();
}

void GridRenderer::initialize()
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
            FragColor = vec4(0.6, 0.6, 0.6, 1.0);
        })";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();

    buildGrid(20,1.0f);
}


void GridRenderer::render(const Camera &camera)
{
    program.bind();



        QMatrix4x4 mvp = camera.projectionMatrix() * camera.viewMatrix();
        program.setUniformValue("mvp", mvp);

        vao.bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
        vao.release();

        program.release();
}

void GridRenderer::buildGrid(int halfSize, float spacing)
{
    QVector<float> vertices; //load up vertices {x0,y0,z0...}

    for (int i{-halfSize}; i <=halfSize; ++i)
    {
        float p = i * spacing;

        //parallel lines to x axis
        vertices<< - halfSize * spacing << 0.0f << p;
        vertices<< halfSize * spacing << 0.0f <<p;
        //parallel lines to z axis
        vertices<< p << 0.0f << -halfSize * spacing;
        vertices<< p << 0.0f << halfSize * spacing;
    }

    vertexCount = vertices.size()/3;

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices.constData(), vertices.size()* sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), nullptr);

    vbo.release();
    vao.release();
}
