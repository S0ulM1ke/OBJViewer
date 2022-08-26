//#include "widget.h"
#include "mainwidget.h"

//#include <QSurfaceFormat>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    setlocale(LC_NUMERIC, "C");
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWidget w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
