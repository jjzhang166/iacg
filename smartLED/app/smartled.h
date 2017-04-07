#ifndef SMARTLED_H
#define SMARTLED_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>
#include <QtQml>
#include <QTranslator>
#include <QSplashScreen>
#include <QPixmap>
#include <QMessageBox>

#include "app/serialportmanager.h"
#include "app/mailmanager.h"
#include "app/fontmanager.h"
#include "app/datamanager.h"
#include "app/bootmanager.h"

class SmartLED : public QObject
{
    Q_OBJECT
public:
    explicit SmartLED(const QString &pixmap, const QString &cfgfile="cfg.ini", QObject *parent = 0);
    ~SmartLED();

public slots:
    void onObjectCreated(QObject* ,QUrl);

private:
    BootManager *bootmanager;
    DataManager *datamanager;
    FontManager *fontmanager;
    MailManager *mailmanager;
    SerialportManager *serialportmanager;
    QQmlApplicationEngine *engine;
    QSplashScreen *splash;
};

#endif // SMARTLED_H
