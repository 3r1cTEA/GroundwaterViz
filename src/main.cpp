#include <QApplication>
#include "ui/MainWindow.h"
#include "core/Grid3D.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow w;
    w.resize(800, 600);
    w.show();




    return app.exec();
}
