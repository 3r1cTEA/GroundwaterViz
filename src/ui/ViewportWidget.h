#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "TriangleRenderer.h"


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
    TriangleRenderer triangle;
};


