#include "application.h"
#include "smartled.h"

Application::Application(const QString &pixmap, QObject *parent) : QObject(parent) {
    QDir splash_file(QDir::currentPath() + "/splash.png");
    splash = (QDir::current().exists("splash.png")) ? new QSplashScreen(QPixmap(splash_file.absolutePath()))
                                    : new QSplashScreen(QPixmap(pixmap));
    splash->show();
    splash->showMessage("program init...");
    SmartLED::init();
    splash->showMessage("QML Engine:loading,please wait...");
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
        if(!SmartLED::datamanager->ReadBootData(DataManager::BOOT_SMTP).toBool())
            goto serialportInit;
		splash->showMessage("MailManager:create SMTP object");
        if(!SmartLED::mailmanager->trytoCreateSmtpInstance()) {
            splash->showMessage("MailManager:create SMTP object failed");
            QMessageBox::information(NULL,tr("info"), tr("MailManager:create SMTP object failed"),
                                     QMessageBox::Yes);
        }

        serialportInit:
        if(!SmartLED::datamanager->ReadBootData(DataManager::BOOT_SERIALPORT).toBool())
            goto splashEnd;
        splash->showMessage("SerialManager:try to connect " + SmartLED::serialportmanager->portName());
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
