#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QPoint>
#include <QKeyEvent>

#include "TriangleRenderer.h"
#include "Camera.h"
#include "GridRenderer.h"


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

    //keys baby
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Camera camera;
    TriangleRenderer triangle;
    GridRenderer grid;

    bool mouseLookEnabled = false;
    QPoint lastMousePos;
};


