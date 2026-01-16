#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class TriangleRenderer: protected QOpenGLFunctions
{
public:
    TriangleRenderer();
    ~TriangleRenderer();

    void initialize();
    void render();

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;

};
