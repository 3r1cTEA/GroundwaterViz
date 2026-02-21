#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

#include "IRenderer.h"
#include "Camera.h"
#include "GridMesh.h"

class FilledGridRenderer: protected QOpenGLFunctions, public IRenderer
{
public:
    FilledGridRenderer(const GridMesh& mesh);
    ~FilledGridRenderer();

    void initialize() override;
    void render(const Camera& camera) override;

private:
    const GridMesh m_mesh;
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer ebo{QOpenGLBuffer::IndexBuffer};
    QOpenGLVertexArrayObject vao;

    int indexCount{0};



};


