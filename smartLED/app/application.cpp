#include "application.h"
#include "smartled.h"
#include <QUnhandledException>

Application::Application(QObject *parent) : QObject(parent) {
    SmartLED::splash->showMessage("QML Engine:loading,please wait...", Qt::AlignLeft, SmartLED::splash_color);
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
#ifdef QT_DEBUG
    qDebug() << "destroy application";
#endif
}

void Application::onWindowClosed(QQuickCloseEvent *) {
    QDir rootdir(SmartLED::workpath);
    if(!rootdir.exists("frame.ini")) {
        QMessageBox::StandardButton retBtn = QMessageBox::information(NULL, QObject::tr("info"),
                                 QObject::tr("file 'frame.ini' is not exist, save the current config?"),
                                 QMessageBox::Yes, QMessageBox::No);
        if(retBtn == QMessageBox::Yes)
            Frame::saveFrame(SmartLED::workpath + "/frame.ini");
    }
    QSettings ini_setting(SmartLED::workpath + "/cfg.ini", QSettings::IniFormat);
    ini_setting.setValue("Boot/WinShadow", winshadow);
}

void Application::onObjectCreated(QObject* obj, QUrl url) {
    Q_UNUSED(url)
    if(obj != nullptr) {
        if(!SmartLED::bootmanager->smtpBoot())
            goto serialportInit;
        SmartLED::splash->showMessage("MailManager:create SMTP object", Qt::AlignLeft, SmartLED::splash_color);
        if(!SmartLED::mailmanager->trytoCreateSmtpInstance()) {
            SmartLED::splash->showMessage("MailManager:create SMTP object failed", Qt::AlignLeft, SmartLED::splash_color);
            QMessageBox::information(NULL, tr("info"), tr("MailManager:create SMTP object failed"),
                                     QMessageBox::Yes);
        }

        serialportInit:
        QObject *window1 = nullptr;
        foreach (QObject *obj, engine->rootObjects())
            if(obj->objectName() == "obj_window1")
                window1 = obj;
        if(window1 == nullptr) {
            SmartLED::splash->showMessage("QML Engine:find qml object error",
                                          Qt::AlignLeft, SmartLED::splash_color);
            QMessageBox::critical(NULL, tr("error"), tr("QML:find qml object error"), QMessageBox::Yes);
            throw new QUnhandledException;
        }
        QSettings ini_setting(SmartLED::workpath + "/cfg.ini", QSettings::IniFormat);
        winshadow = ini_setting.value("Boot/WinShadow", true).toBool();
        if(!winshadow)
            QMetaObject::invokeMethod(window1, "closeWinShadow");

        if(!SmartLED::bootmanager->serialportBoot())
            goto splashEnd;
        SmartLED::splash->showMessage("SerialManager:try to connect " + SmartLED::serialportmanager->portName(),
                                      Qt::AlignLeft, SmartLED::splash_color);

        QObject *button1 = nullptr;
        button1 = obj->findChild<QObject*>("obj_window1_button1");
        if(button1 == nullptr) {
            SmartLED::splash->showMessage("QML Engine:find qml object error",
                                          Qt::AlignLeft, SmartLED::splash_color);
            QMessageBox::critical(NULL, tr("error"), tr("QML:find qml object error"), QMessageBox::Yes);
            throw new QUnhandledException;
        }
        QMetaObject::invokeMethod(button1,"initSerialportConnect");

        splashEnd:
        QObject::connect(window1, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onWindowClosed(QQuickCloseEvent*)));
        SmartLED::splash->close();
        delete SmartLED::splash;
        SmartLED::splash = nullptr;
    }
    else {
        SmartLED::splash->showMessage("QML Engine:init error", Qt::AlignLeft, SmartLED::splash_color);
        QMessageBox::critical(NULL, tr("error"), tr("QML:engine load failed"), QMessageBox::Yes);
        throw new QUnhandledException;
    }
}
