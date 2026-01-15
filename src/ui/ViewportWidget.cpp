#include "ViewportWidget.h"
#include <QDebug>

ViewportWidget::ViewportWidget(QWidget* parent): QOpenGLWidget(parent)
{

}

void ViewportWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    qDebug()<< "OpenGL initialized";

    //Shaders
    const char *vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        })";

    const char *fragmentShader = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 0.6, 0.2, 1.0);
        })";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();

    //triangle points
    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    vao.create();
    vao.bind();

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    program.bind();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 3);

    vbo.release();
    vao.release();
    program.release();
}

void ViewportWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void ViewportWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    vao.bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    vao.release();
    program.release();
}
