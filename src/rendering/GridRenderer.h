#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Camera.h"
#include "IRenderer.h"


class GridRenderer:protected QOpenGLFunctions, public IRenderer
{
public:
    GridRenderer();
    ~GridRenderer();

    void initialize() override;
    void render(const Camera& camera) override;

private:

    void buildGrid(int halfSize, float spacing);

    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;

    int vertexCount = 0;
};


