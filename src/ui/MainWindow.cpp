#include "MainWindow.h"
#include "ViewportWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
auto* viewport = new ViewportWidget(this);
setCentralWidget(viewport);
}
