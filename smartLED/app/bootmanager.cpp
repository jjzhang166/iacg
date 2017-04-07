#include "bootmanager.h"
#include <QDebug>

BootManager::BootManager(DataManager *dm ,QObject *parent) :
    QObject(parent),
    datamanager(dm) {
    m_smtpBoot = dm->ReadBootData(DataManager::BOOT_SMTP).toBool();
    m_serialportBoot = dm->ReadBootData(DataManager::BOOT_SERIALPORT).toBool();
}

BootManager::~BootManager() {
    datamanager->WriteBootData(DataManager::BOOT_SMTP, m_smtpBoot);
    datamanager->WriteBootData(DataManager::BOOT_SERIALPORT, m_serialportBoot);
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
