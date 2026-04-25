#include "ViewportWidget.h"
#include "ModflowReader.h"
#include <QDebug>


ViewportWidget::ViewportWidget(QWidget* parent): QOpenGLWidget(parent),grid(0,0,0,1.0f,1.0f,1.0f)   // test grid
{

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

}

void ViewportWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);



    Grid3D grid = ModflowReader::load("../assets/test_grid.txt");
    mesh = GridMesh::fromGrid3D(grid);

        //qDebug << "Mesh vertices: " << mesh.vertices().size();
        qDebug() << "Mesh vertices:" << mesh.vertices().size();
        qDebug() << "Mesh indices:" << mesh.indices().size();
        qDebug() << "Grid head[0]:" << grid.head()[0];

    glEnable(GL_DEPTH_TEST);



    //renderers.push_back(std::make_unique<TriangleRenderer>());
    renderers.push_back(std::make_unique<GridRenderer>());
    renderers.push_back(std::make_unique<AxisRenderer>());
    //renderers.push_back(std::make_unique<GridLineRenderer>());
    renderers.push_back(std::make_unique<FilledGridRenderer>(mesh));

    qDebug()<<renderers.size();
    for (auto& r : renderers)
        r->initialize();

}

void ViewportWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    float aspect = float(w) / float(h);
    camera.setAspectRatio(aspect);
    //axis.setAspectRatio(aspect);
}

void ViewportWidget::paintGL()
{
    //glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& r : renderers)
        r->render(camera);

}

void ViewportWidget::keyPressEvent(QKeyEvent *event)
{
    constexpr float speed = 0.5f;

    switch(event->key())
    {
        case Qt::Key_W: camera.moveForward((speed)); break;
        case Qt::Key_S: camera.moveForward(-speed); break;
        case Qt::Key_A: camera.moveRight(-speed); break;
        case Qt::Key_D: camera.moveRight(speed); break;
        case Qt::Key_Q: camera.moveUp(speed); break;
        case Qt::Key_E: camera.moveUp(-speed); break;
    }
    update();
}

void ViewportWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouseLookEnabled = true;
        lastMousePos = event->pos();
        setCursor(Qt::BlankCursor);
    }
}

void ViewportWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouseLookEnabled = false;
        unsetCursor();
    }
}

void ViewportWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mouseLookEnabled)
        return;

    QPoint delta = event->pos() - lastMousePos;
    lastMousePos = event->pos();

    const float sensitivity = 0.2f;

    camera.yaw(delta.x() * sensitivity);
    camera.pitch(-delta.y() * sensitivity);

    update();
}
