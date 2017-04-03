#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVariant>
#include <QtQml>
#include <QTranslator>

#include "serialconnect.h"
#include "maildata.h"
#include "fontmanager.h"
#include "datamanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    app.installTranslator(&ts);
    DataManager dm("cfg.ini");
    QQmlApplicationEngine engine;
    FontManager *fontmanager = new FontManager(&dm);
    engine.rootContext()->setContextProperty("fontmanager",fontmanager);
    MailData *maildata = new MailData(&dm);
    engine.rootContext()->setContextProperty("maildata",maildata);
    serialConnect *sc = new serialConnect(&dm);
    engine.rootContext()->setContextProperty("sc",sc);
    engine.addImportPath(QDir::currentPath());
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    app.exec();
    delete sc;
    delete maildata;
    delete fontmanager;
}
