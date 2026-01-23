#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Camera.h"
#include "IRenderer.h"

class TriangleRenderer: protected QOpenGLFunctions, public IRenderer
{
public:
    TriangleRenderer();
    ~TriangleRenderer();

    void initialize() override;

    void render(const Camera& camera) override;

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;



};
