#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <Camera.h>


class GridRenderer:protected QOpenGLFunctions
        /// not inheriting from trianglerenderer as I hope to clear it out later
{
public:
    GridRenderer();
    ~GridRenderer();

    void initialize();

    //void resize(int w, int h);

    void setAspectRatio(float aspect);
    void render(const Camera& camera);





private:

    void buildGrid(int halfSize, float spacing);

    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;

    int vertexCount = 0;
    float aspectRatio = 1.0f;
};


