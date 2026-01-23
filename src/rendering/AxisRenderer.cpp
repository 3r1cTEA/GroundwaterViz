#include "AxisRenderer.h"

#include <QMatrix4x4>
#include <QOpenGLFunctions>

AxisRenderer::AxisRenderer()
{

}

AxisRenderer::~AxisRenderer()
{
vao.destroy();
vbo.destroy();
}

void AxisRenderer::initialize()
{
    float axisVertices[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(axisVertices, sizeof(axisVertices));

    const char *vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        uniform mat4 mvp;
        out vec3 vColor;


        void main()
        {
            vColor = color;
            gl_Position = mvp * vec4(position, 1.0);
        })";

    const char *fragmentShader = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(vColor, 1.0);
        })";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();

    program.bind();

    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(float));

    program.enableAttributeArray(1);
    program.setAttributeBuffer(1, GL_FLOAT, 3*sizeof(float), 3, 6*sizeof(float));

    vao.release();
    vbo.release();
    program.release();
}

void AxisRenderer::render(const Camera &camera)
{
    QMatrix4x4 mvp = camera.projectionMatrix()*camera.viewMatrix();

    program.bind();
    program.setUniformValue("mvp", mvp);

    vao.bind();
    glDrawArrays(GL_LINES, 0, 6);
    vao.release();

    program.release();
}
