#include "smartled.h"
#include <QUnhandledException>

SmartLED::SmartLED(const QString &pixmap, const QString &cfgfile, QObject *parent) : QObject(parent) {
    splash = new QSplashScreen(QPixmap(pixmap));
    splash->show();
    splash->showMessage("QML Engine:loading,please wait...");
    engine = new QQmlApplicationEngine;
    QObject::connect(engine,SIGNAL(objectCreated(QObject*,QUrl)),this,SLOT(onObjectCreated(QObject*,QUrl)));
    datamanager = new DataManager(cfgfile);
    qmlRegisterUncreatableType<SerialportManager>("Manager.Serialport",1,0,"SerialportManager",QString("Static Class"));
    qmlRegisterUncreatableType<MailManager>("Manager.Mail",1,0,"MailManager",QString("Static Class"));
    fontmanager = new FontManager(datamanager);
    engine->rootContext()->setContextProperty("fontmanager", fontmanager);
    mailmanager = new MailManager(datamanager);
    engine->rootContext()->setContextProperty("maildata", mailmanager);
    serialportmanager = new SerialportManager(datamanager);
    engine->rootContext()->setContextProperty("sc", serialportmanager);
    engine->addImportPath(QDir::currentPath());
    engine->load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
}

SmartLED::~SmartLED() {
    delete serialportmanager;
    delete fontmanager;
    delete mailmanager;
    delete datamanager;
    delete engine;
}

void SmartLED::onObjectCreated(QObject* obj, QUrl url) {
    Q_UNUSED(url)
    if(obj != nullptr) {
        splash->showMessage("QML Engine:init ok");
        splash->close();
        delete splash;
    }
    else {
        splash->showMessage("QML Engine:init error");
        QMessageBox::critical(NULL,"error","QML:engine load failed",QMessageBox::Yes);
        splash->close();
        delete splash;
        throw new QUnhandledException;
    }
}
