#include "smartled.h"
#include <QUnhandledException>

SmartLED::SmartLED(const QString &pixmap, const QString &cfgfile, QObject *parent) : QObject(parent) {
    QDir splash_file(QDir::currentPath() + "/splash.png");
    splash = (QDir::current().exists("splash.png")) ? new QSplashScreen(QPixmap(splash_file.absolutePath()))
                                    : new QSplashScreen(QPixmap(pixmap));
    splash->show();
    splash->showMessage("QML Engine:loading,please wait...");
    engine = new QQmlApplicationEngine;
    QObject::connect(engine,SIGNAL(objectCreated(QObject*,QUrl)),this,SLOT(onObjectCreated(QObject*,QUrl)));
    datamanager = new DataManager(cfgfile);
    qmlRegisterUncreatableType<SerialportManager>("Manager.Serialport",1,0,"SerialportManager",QString("Static Class"));
    qmlRegisterUncreatableType<MailManager>("Manager.Mail",1,0,"MailManager",QString("Static Class"));
    bootmanager = new BootManager(datamanager);
    engine->rootContext()->setContextProperty("bootmanager", bootmanager);
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
    delete bootmanager;
    delete serialportmanager;
    delete fontmanager;
    delete mailmanager;
    delete datamanager;
    delete engine;
}

void SmartLED::onObjectCreated(QObject* obj, QUrl url) {
    Q_UNUSED(url)
    if(obj != nullptr) {
        if(!datamanager->ReadBootData(DataManager::BOOT_SMTP).toBool())
            goto serialportInit;
		splash->showMessage("MailManager:create SMTP object");
        if(!mailmanager->trytoCreateSmtpInstance()) {
            splash->showMessage("MailManager:create SMTP object failed");
            QMessageBox::information(NULL,tr("info"), tr("MailManager:create SMTP object failed"),
                                     QMessageBox::Yes);
        }

        serialportInit:
        if(!datamanager->ReadBootData(DataManager::BOOT_SERIALPORT).toBool())
            goto splashEnd;
        splash->showMessage("SerialManager:try to connect "+serialportmanager->portName());
        QObject *button1 = nullptr;
        foreach(QObject *obj,engine->rootObjects())
            if(obj->objectName() == "obj_window1") {
                button1 = obj->findChild<QObject*>("obj_window1_button1");
            }
        if(button1 == nullptr) {
            splash->showMessage("QML Engine:find qml object error");
            QMessageBox::critical(NULL, tr("error"), tr("QML:find qml object error"), QMessageBox::Yes);
            delete splash;
            throw new QUnhandledException;
        }
        QMetaObject::invokeMethod(button1,"initSerialportConnect");

        splashEnd:
        splash->close();
        delete splash;
    }
    else {
        splash->showMessage("QML Engine:init error");
        QMessageBox::critical(NULL, tr("error"), tr("QML:engine load failed"), QMessageBox::Yes);
        splash->close();
        delete splash;
        throw new QUnhandledException;
    }
}
