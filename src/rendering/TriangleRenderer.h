#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Camera.h"

class TriangleRenderer: protected QOpenGLFunctions
{
public:
    TriangleRenderer();
    ~TriangleRenderer();

    void initialize();
    void resize(int w, int h);

    void setAspectRatio(float aspect);
    void render(const Camera& camera);

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;

    float aspectRatio = 1.0f;

};
