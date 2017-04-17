#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QSplashScreen>
#include <QPixmap>
#include <QMessageBox>
#include <QUnhandledException>

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(const QString &pixmap = ":/splash.png", QObject *parent = 0);
    ~Application();

public slots:
    void onObjectCreated(QObject* ,QUrl);

private:
    QQmlApplicationEngine *engine;
    QSplashScreen *splash;
};

#endif // APPLICATION_H
