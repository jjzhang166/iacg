#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVariant>
#include <QtQml>
#include <QTranslator>

#include "app/serialportmanager.h"
#include "app/mailmanager.h"
#include "app/fontmanager.h"
#include "app/datamanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    app.installTranslator(&ts);
    DataManager *dm = new DataManager("cfg.ini");
    QQmlApplicationEngine engine;
    qmlRegisterUncreatableType<SerialportManager>("Manager.Serialport",1,0,"SerialportManager",QString("Static Class"));
    qmlRegisterUncreatableType<MailManager>("Manager.Mail",1,0,"MailManager",QString("Static Class"));
    FontManager *fontmanager = new FontManager(dm);
    engine.rootContext()->setContextProperty("fontmanager", fontmanager);
    MailManager *mailmanager = new MailManager(dm);
    engine.rootContext()->setContextProperty("maildata", mailmanager);
    SerialportManager *serialportmanager = new SerialportManager(dm);
    engine.rootContext()->setContextProperty("sc", serialportmanager);
    engine.addImportPath(QDir::currentPath());
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    app.exec();
    delete serialportmanager;
    delete mailmanager;
    delete fontmanager;
    delete dm;
}
