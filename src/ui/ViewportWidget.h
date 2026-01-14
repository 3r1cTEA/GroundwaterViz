#pragma once

#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


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
};

#endif // VIEWPORTWIDGET_H
