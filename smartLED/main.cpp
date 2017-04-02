﻿#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVariant>
#include <QtQml>
#include <QTranslator>

#include "serialconnect.h"
#include "maildata.h"
#include "fontmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    app.installTranslator(&ts);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("fontmanager",new FontManager);
    engine.rootContext()->setContextProperty("maildata",new MailData);
    engine.rootContext()->setContextProperty("sc",new serialConnect);
    engine.addImportPath(QDir::currentPath());
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
    return app.exec();
}
