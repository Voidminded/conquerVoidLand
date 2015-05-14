#include "mainwindow.h"
#include <QTime>
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    CMonitorWidget mon;
//    mon.show();

    return a.exec();
}
