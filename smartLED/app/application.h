#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QMessageBox>
#include <QUnhandledException>

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();

public slots:
    void onObjectCreated(QObject* ,QUrl);

private:
    QQmlApplicationEngine *engine;
};

#endif // APPLICATION_H
