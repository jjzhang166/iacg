#include "notifymanager.h"
#include <QUnhandledException>
#include <QDebug>

NotifyManager::NotifyManager(const QString &filepath, const QString &inifile, const QString &dll, QObject *parent)
    : QObject(parent), medialib(dll), ini_setting(inifile, QSettings::IniFormat) {
    if(!medialib.load()) {
        qDebug() << "load dll error";
        throw new QUnhandledException;
    }

    _mciSendString = (MediaFunc)medialib.resolve("mciSendStringW");
    if(_mciSendString == nullptr) {
        qDebug() << "resolve dll error";
        throw new QUnhandledException;
    }

    QString opendevice = "OPEN " + filepath + " TYPE MPEGVIDEO ALIAS alertsound";
    MCIERROR retCode;
    retCode = _mciSendString(opendevice.toStdWString().c_str(), NULL, 0, NULL);
    if(retCode) {
        qDebug() << "open device error";
        throw new QUnhandledException;
    }

    m_notifyEnable = ini_setting.value("Notify/NotifyEnable", false).toBool();
    m_notifyTemp = ini_setting.value("Notify/NotifyTemp", INT_MAX).toInt();
    m_notifyHumi = ini_setting.value("Notify/NotifyHumi", INT_MAX).toInt();
    m_notifyLL = ini_setting.value("Notify/NotifyLL", 0).toInt();
}

NotifyManager::~NotifyManager() {
    medialib.unload();
    ini_setting.setValue("Notify/NotifyEnable", m_notifyEnable);
    ini_setting.setValue("Notify/NotifyTemp", m_notifyTemp);
    ini_setting.setValue("Notify/NotifyHumi", m_notifyHumi);
    ini_setting.setValue("Notify/NotifyLL", m_notifyLL);
}

bool NotifyManager::playAlertSound() {
    QString playsound = "PLAY alertsound NOTIFY REPEAT";
    MCIERROR retCode = _mciSendString(playsound.toStdWString().c_str(), NULL, 0, NULL);
    if(retCode) return false;
    return true;
}

bool NotifyManager::stopAlertSound() {
    MCIERROR retCode;
    QString stopsound = "STOP alertsound";
    retCode = _mciSendString(stopsound.toStdWString().c_str(), NULL, 0 ,NULL);
    if(retCode) {
        qDebug() << "stop media error";
        return false;
    }
    return true;
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
