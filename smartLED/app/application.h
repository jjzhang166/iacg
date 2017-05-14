/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQuickWindow>

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();

public slots:
    void onObjectCreated(QObject* ,QUrl);
    void onWindowClosed(QQuickCloseEvent*);

private:
    QQmlApplicationEngine *engine;
    bool winshadow;
};

#endif // APPLICATION_H
