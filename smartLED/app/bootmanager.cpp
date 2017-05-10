#include "bootmanager.h"
#include <QDebug>

BootManager::BootManager(QObject *parent) :
    QObject(parent),
    ini_setting("cfg.ini", QSettings::IniFormat) {
    m_smtpBoot = ini_setting.value("Boot/SmtpBoot", false).toBool();
    m_serialportBoot = ini_setting.value("Boot/SerialportBoot", false).toBool();
}

BootManager::~BootManager() {
    qDebug() << "destroy boot manager";
    ini_setting.setValue("Boot/SmtpBoot", m_smtpBoot);
    ini_setting.setValue("Boot/SerialportBoot", m_serialportBoot);
}

bool BootManager::smtpBoot() const {
    return this->m_smtpBoot;
}

bool BootManager::serialportBoot() const {
    return this->m_serialportBoot;
}

void BootManager::setSmtpBoot(const bool isboot) {
    m_smtpBoot = isboot;
}

void BootManager::setSerialportBoot(const bool isboot) {
    m_serialportBoot = isboot;
}
