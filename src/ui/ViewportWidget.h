#pragma once

#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


class ViewportWidget: public QOpenGLWidget,
                       protected QOpenGLFunctions
{
    Q_OBJECT
public:
   explicit ViewportWidget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;
};

#endif // VIEWPORTWIDGET_H
