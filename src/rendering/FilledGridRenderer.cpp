#include "FilledGridRenderer.h"


#include <QVector3D>
#include <vector>

FilledGridRenderer::FilledGridRenderer()
{

}

FilledGridRenderer::~FilledGridRenderer()
{

}

void FilledGridRenderer::initialize()
{
    initializeOpenGLFunctions();

    const char *vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        uniform mat4 mvp;
        void main()
        {
            gl_Position = mvp * vec4(position, 1.0);
        })";

    const char *fragmentShader = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.5, 0.5, 0.5, 1.0);
        })";

    program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program.link();


    vao.create();
    vbo.create();
    ebo.create();

    buildGrid();
}

void FilledGridRenderer::render(const Camera &camera)
{
    program.bind();
    vao.bind();

    QMatrix4x4 mvp = camera.projectionMatrix() * camera.viewMatrix();

    program.setUniformValue("mvp", mvp);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    vao.release();

    program.release();

}

void FilledGridRenderer::buildGrid()
{
std::vector<QVector3D> vertices;
std::vector<unsigned int> indices;

    for (int i {0}; i < nx; ++i)
    {
        for (int j{0}; j < ny; ++j)
        {
            for (int k{0}; k < nz; ++k)
            {
                float xa = i * dx;
                float xb = (i + 1) * dx;
                float ya = j * dy;
                float yb = (j + 1) * dy;
                float za = k * dz;
                float zb = (k + 1) * dz;

                QVector3D paaa(xa, ya, za);
                QVector3D pbaa(xb, ya, za);
                QVector3D paba(xa, yb, za);
                QVector3D pbba(xb, yb, za);
                QVector3D paab(xa, ya, zb);
                QVector3D pbab(xb, ya, zb);
                QVector3D pabb(xa, yb, zb);
                QVector3D pbbb(xb, yb, zb);

                //zfaces
                addQuad(vertices, indices, paaa, pbaa, pbba, paba);
                addQuad(vertices, indices, paab, pbab, pbbb, pabb);

                //xfaces
                addQuad(vertices, indices, paaa, paba, pabb, paab);
                addQuad(vertices, indices, pbaa, pbba, pbbb, pbab);

                //yfaces
                addQuad(vertices, indices, paaa, pbaa, pbab, paab);
                addQuad(vertices, indices, paba, pbba, pbbb, pabb);

            }
        }
    }
    indexCount = indices.size();

    vao.bind();

    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size()*( sizeof(QVector3D)));

    ebo.bind();
    ebo.allocate(indices.data(), indices.size()*sizeof(unsigned int));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), nullptr);

    vao.release();

}

void FilledGridRenderer::addQuad(std::vector<QVector3D> &vertices, std::vector<unsigned int> &indices, const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d)
{
unsigned int start = vertices.size();
vertices.push_back(a);
vertices.push_back(b);
vertices.push_back(c);
vertices.push_back(d);

indices.insert(indices.end(), {
                   start, start + 1, start + 2,
                   start, start + 2, start + 3
               });

}
