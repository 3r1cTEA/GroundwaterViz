#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

#include "IRenderer.h"
#include "Camera.h"

class FilledGridRenderer: protected QOpenGLFunctions, public IRenderer
{
public:
    FilledGridRenderer();
    ~FilledGridRenderer();

    void initialize() override;
    void render(const Camera& camera) override;

private:
    void buildGrid();
    void addQuad(
            std::vector<QVector3D>& vertices,
            std::vector<unsigned int>& indices,
            const QVector3D& a,
            const QVector3D& b,
            const QVector3D& c,
            const QVector3D& d);

    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer ebo{QOpenGLBuffer::IndexBuffer};
    QOpenGLVertexArrayObject vao;

    int indexCount{0};


        int nx{10};
        int ny{5};
        int nz{10};
        float dx{1.0f};
        float dy{1.0f};
        float dz{1.0f};
};
