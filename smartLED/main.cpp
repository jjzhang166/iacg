#include <QApplication>
#include <QTranslator>
#include "app/smartled.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    app.installTranslator(&ts);
    try {
        SmartLED *sl = new SmartLED(":/splash.png");
        app.exec();
        delete sl;
    }
    catch(...) {
        app.quit();
    }
}
