#include "bootmanager.h"
#include <QDebug>

BootManager::BootManager(const QString &filename, QObject *parent) :
    QObject(parent),
    ini_setting(filename, QSettings::IniFormat) {
    m_smtpBoot = ini_setting.value("Boot/SmtpBoot", false).toBool();
    m_serialportBoot = ini_setting.value("Boot/SerialportBoot", false).toBool();
    m_winShadow = ini_setting.value("Boot/WinShadow", true).toBool();
}

BootManager::~BootManager() {
#ifdef QT_DEBUG
    qDebug() << "destroy boot manager";
#endif
    ini_setting.setValue("Boot/SmtpBoot", m_smtpBoot);
    ini_setting.setValue("Boot/SerialportBoot", m_serialportBoot);
    ini_setting.setValue("Boot/WinShadow", m_winShadow);
}

bool BootManager::smtpBoot() const {
    return this->m_smtpBoot;
}

bool BootManager::serialportBoot() const {
    return this->m_serialportBoot;
}

bool BootManager::winShadow() const {
    return this->m_winShadow;
}

void BootManager::setSmtpBoot(const bool isboot) {
    m_smtpBoot = isboot;
}

void BootManager::setSerialportBoot(const bool isboot) {
    m_serialportBoot = isboot;
}

void BootManager::setWinShadow(const bool isboot) {
    m_winShadow = isboot;
}
