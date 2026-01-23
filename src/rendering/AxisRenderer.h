#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "Camera.h"
#include "IRenderer.h"


class AxisRenderer: public IRenderer
{
public:
    AxisRenderer();
    ~AxisRenderer();

    void initialize() override;
    void render(const Camera& camera) override;

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;
};

