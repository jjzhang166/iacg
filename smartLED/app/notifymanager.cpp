#include "notifymanager.h"
#include <QUnhandledException>
#include <QDebug>
#include <QMessageBox>
#include <limits>
#include <Windows.h>

NotifyManager::NotifyManager(const QString &filepath, const QString &inifile, QObject *parent)
    : QObject(parent), ini_setting(inifile, QSettings::IniFormat) {
    m_notifyEnable = ini_setting.value("Notify/NotifyEnable", false).toBool();
    m_notifyTemp = ini_setting.value("Notify/NotifyTemp", INT_MAX).toInt();
    m_notifyHumi = ini_setting.value("Notify/NotifyHumi", INT_MAX).toInt();
    m_notifyLL = ini_setting.value("Notify/NotifyLL", 0).toInt();
    m_notifyValid = true;
    QString opendevice = "OPEN " + filepath + " TYPE MPEGVIDEO ALIAS alertsound";
    MCIERROR retCode;
    WCHAR buf[512];
    retCode = mciSendStringW(opendevice.toStdWString().c_str(), NULL, 0, NULL);
    if(retCode) {
        mciGetErrorStringW(retCode, buf, sizeof(buf));
        QString mciError = QString::fromStdWString(std::wstring(buf));
        QMessageBox::critical(NULL, tr("error"),
                              "mciSendString:" + mciError, QMessageBox::Ok);
        m_notifyValid = false;
        m_notifyEnable = false;
    }
}

NotifyManager::~NotifyManager() {
    ini_setting.setValue("Notify/NotifyEnable", m_notifyEnable);
    ini_setting.setValue("Notify/NotifyTemp", m_notifyTemp);
    ini_setting.setValue("Notify/NotifyHumi", m_notifyHumi);
    ini_setting.setValue("Notify/NotifyLL", m_notifyLL);
}

bool NotifyManager::playAlertSound() {
    MCIERROR retCode;
    QString playsound = "PLAY alertsound NOTIFY REPEAT";
    retCode = mciSendStringW(playsound.toStdWString().c_str(), NULL, 0, NULL);
    if(retCode) return false;
    return true;
}

bool NotifyManager::stopAlertSound() {
    MCIERROR retCode;
    QString stopsound = "STOP alertsound";
    retCode = mciSendStringW(stopsound.toStdWString().c_str(), NULL, 0 ,NULL);
    if(retCode) {
#ifdef QT_DEBUG
        qDebug() << "stop media error";
#endif
        return false;
    }
    return true;
}

bool NotifyManager::notifyValid() const {
    return m_notifyValid;
}

bool NotifyManager::notifyEnable() const {
    return m_notifyEnable;
}

int NotifyManager::notifyTemp() const {
    return m_notifyTemp;
}

int NotifyManager::notifyHumi() const {
    return m_notifyHumi;
}

int NotifyManager::notifyLL() const {
    return m_notifyLL;
}

void NotifyManager::setNotifyEnable(const bool ne) {
    m_notifyEnable = ne;
}

void NotifyManager::setNotifyTemp(const int nt) {
    m_notifyTemp = nt;
}

void NotifyManager::setNotifyHumi(const int nh) {
    m_notifyHumi = nh;
}

void NotifyManager::setNotifyLL(const int nll) {
    m_notifyLL = nll;
}
