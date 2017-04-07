#ifndef BOOTMANAGER_H
#define BOOTMANAGER_H

#include <QObject>
#include "datamanager.h"

class BootManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool smtpBoot READ smtpBoot WRITE setSmtpBoot NOTIFY smtpBootChanged)
    Q_PROPERTY(bool serialportBoot READ serialportBoot WRITE setSerialportBoot NOTIFY serialportBootChanged)

public:
    explicit BootManager(DataManager *dm, QObject *parent = 0);
    ~BootManager();

signals:
    void smtpBootChanged(const bool smtpBoot);
    void serialportBootChanged(const bool serialportBoot);

public:
    bool smtpBoot() const;
    void setSmtpBoot(const bool);

    bool serialportBoot() const;
    void setSerialportBoot(const bool);

private:
    DataManager *datamanager;
    bool m_smtpBoot;
    bool m_serialportBoot;
};

#endif // BOOTMANAGER_H
