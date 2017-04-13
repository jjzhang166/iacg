#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    a.installTranslator(&ts);
    MainWindow w;
    w.setWindowTitle(QObject::tr("frameCreator"));
    w.show();

    return a.exec();
}
