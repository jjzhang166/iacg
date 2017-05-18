/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/
#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QObject>
#include <QLibrary>
#include <QSettings>

class NotifyManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool notifyValid READ notifyValid CONSTANT)
    Q_PROPERTY(bool notifyEnable READ notifyEnable WRITE setNotifyEnable NOTIFY notifyEnableChanged)
    Q_PROPERTY(int notifyHumi READ notifyHumi WRITE setNotifyHumi NOTIFY notifyHumiChanged)
    Q_PROPERTY(int notifyTemp READ notifyTemp WRITE setNotifyTemp NOTIFY notifyTempChanged)
    Q_PROPERTY(int notifyLL READ notifyLL WRITE setNotifyLL NOTIFY notifyLLChanged)

public:
    explicit NotifyManager(const QString &filepath,
                           const QString &inifile,
                           QObject *parent = 0);
    ~NotifyManager();

signals:
    void notifyEnableChanged();
    void notifyHumiChanged();
    void notifyTempChanged();
    void notifyLLChanged();

public:
    bool notifyValid() const;
    bool notifyEnable() const;
    int notifyHumi() const;
    int notifyTemp() const;
    int notifyLL() const;
    void setNotifyValid(const bool nv);
    void setNotifyEnable(const bool ne);
    void setNotifyHumi(const int nh);
    void setNotifyTemp(const int nt);
    void setNotifyLL(const int nll);

public:
    Q_INVOKABLE bool playAlertSound();
    Q_INVOKABLE bool stopAlertSound();

private:
    QSettings ini_setting;
    bool m_notifyValid;
    bool m_notifyEnable;
    int  m_notifyHumi;
    int  m_notifyTemp;
    int  m_notifyLL;
};

#endif // NOTIFYMANAGER_H
