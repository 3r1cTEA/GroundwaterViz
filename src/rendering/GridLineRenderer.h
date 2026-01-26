#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Camera.h"
#include "IRenderer.h"


class GridLineRenderer: protected QOpenGLFunctions, public IRenderer
{
public:
    GridLineRenderer();
    ~GridLineRenderer();

    void initialize() override;
    void render(const Camera& camera) override;


private:
    void buildGridLines();

    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;

    int vertexCount{0};


    int nx{10};
    int ny{10};
    int nz{10};
    float dx{1.0f};
    float dy{1.0f};
    float dz{1.0f};
};


