/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/
#ifndef BOOTMANAGER_H
#define BOOTMANAGER_H

#include <QObject>
#include <QSettings>

class BootManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool smtpBoot READ smtpBoot WRITE setSmtpBoot NOTIFY smtpBootChanged)
    Q_PROPERTY(bool serialportBoot READ serialportBoot WRITE setSerialportBoot NOTIFY serialportBootChanged)
    Q_PROPERTY(bool winShadow READ winShadow WRITE setWinShadow NOTIFY winShadowChanged)

public:
    explicit BootManager(const QString &filename, QObject *parent = 0);
    ~BootManager();

signals:
    void smtpBootChanged(const bool smtpBoot);
    void serialportBootChanged(const bool serialportBoot);
    void winShadowChanged(const bool winshadow);

public:
    bool smtpBoot() const;
    void setSmtpBoot(const bool);

    bool serialportBoot() const;
    void setSerialportBoot(const bool);

    bool winShadow() const;
    void setWinShadow(const bool);

private:
    QSettings ini_setting;
    bool m_smtpBoot;
    bool m_serialportBoot;
    bool m_winShadow;
};

#endif // BOOTMANAGER_H
