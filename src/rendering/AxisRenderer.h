#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "Camera.h"


class AxisRenderer
{
public:
    AxisRenderer();
    ~AxisRenderer();

    void initialize();
    void render(const Camera& camera);

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;
};

