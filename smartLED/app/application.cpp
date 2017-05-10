#include "application.h"
#include "smartled.h"

Application::Application(QObject *parent) : QObject(parent) {
    SmartLED::splash->showMessage("QML Engine:loading,please wait...");
    engine = new QQmlApplicationEngine;
    QObject::connect(engine,SIGNAL(objectCreated(QObject*,QUrl)),this,SLOT(onObjectCreated(QObject*,QUrl)));
    qmlRegisterUncreatableType<SerialportManager>("Manager.Serialport",1,0,"SerialportManager",QString("Static Class"));
    qmlRegisterUncreatableType<MailManager>("Manager.Mail",1,0,"MailManager",QString("Static Class"));
    engine->rootContext()->setContextProperty("bootmanager", SmartLED::bootmanager.get());
    engine->rootContext()->setContextProperty("fontmanager", SmartLED::fontmanager.get());
    engine->rootContext()->setContextProperty("maildata", SmartLED::mailmanager.get());
    engine->rootContext()->setContextProperty("sc", SmartLED::serialportmanager.get());
    engine->addImportPath(QDir::currentPath());
    engine->load(QUrl(QStringLiteral("qrc:/UI/main.qml")));
}

Application::~Application() {
    delete engine;
}

void Application::onObjectCreated(QObject* obj, QUrl url) {
    Q_UNUSED(url)
    if(obj != nullptr) {
        if(!SmartLED::bootmanager->smtpBoot())
            goto serialportInit;
        SmartLED::splash->showMessage("MailManager:create SMTP object");
        if(!SmartLED::mailmanager->trytoCreateSmtpInstance()) {
            SmartLED::splash->showMessage("MailManager:create SMTP object failed");
            QMessageBox::information(NULL, tr("info"), tr("MailManager:create SMTP object failed"),
                                     QMessageBox::Yes);
        }

        serialportInit:
        if(!SmartLED::bootmanager->serialportBoot())
            goto splashEnd;
        SmartLED::splash->showMessage("SerialManager:try to connect " + SmartLED::serialportmanager->portName());
        QObject *button1 = nullptr;
        foreach(QObject *obj,engine->rootObjects())
            if(obj->objectName() == "obj_window1") {
                button1 = obj->findChild<QObject*>("obj_window1_button1");
            }
        if(button1 == nullptr) {
            SmartLED::splash->showMessage("QML Engine:find qml object error");
            QMessageBox::critical(NULL, tr("error"), tr("QML:find qml object error"), QMessageBox::Yes);
            throw new QUnhandledException;
        }
        QMetaObject::invokeMethod(button1,"initSerialportConnect");

        splashEnd:
        SmartLED::splash->close();
        delete SmartLED::splash;
        SmartLED::splash = nullptr;
    }
    else {
        SmartLED::splash->showMessage("QML Engine:init error");
        QMessageBox::critical(NULL, tr("error"), tr("QML:engine load failed"), QMessageBox::Yes);
        throw new QUnhandledException;
    }
}
