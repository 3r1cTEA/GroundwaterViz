#include "ViewportWidget.h"
#include <QDebug>

ViewportWidget::ViewportWidget(QWidget* parent): QOpenGLWidget(parent)
{

}

void ViewportWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    qDebug()<< "OpenGL initialized";

    triangle.initialize();


}

void ViewportWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void ViewportWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangle.render();
}
