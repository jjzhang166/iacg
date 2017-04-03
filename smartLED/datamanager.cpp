#include "datamanager.h"
#include <QDebug>

DataManager::DataManager(const QString &filename)
    : FileName(filename) {
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    PortName = SetInifile->value("SerialPort/PortName");
    BaudRate = SetInifile->value("SerialPort/BaudRate");
    DataBit = SetInifile->value("SerialPort/DataBit");
    StopBit = SetInifile->value("SerialPort/StopBit");
    Parity = SetInifile->value("SerialPort/Parity");
    User = SetInifile->value("Mail/User");
    Password = SetInifile->value("Mail/Password");
    SendAddr = SetInifile->value("Mail/SendAddr");
    RecvAddr = SetInifile->value("Mail/RecvAddr");
    ServerAddr = SetInifile->value("Mail/ServerAddr");
    Port = SetInifile->value("Mail/Port");
    FontFamily = SetInifile->value("Font/FontFamily");
    delete SetInifile;
}

DataManager::~DataManager() {
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    if(PortName.isValid() && !PortName.toString().isEmpty())
        SetInifile->setValue("SerialPort/PortName", PortName);
    if(BaudRate.isValid() && BaudRate.toInt() > 0)
        SetInifile->setValue("SerialPort/BaudRate",BaudRate);
    if(DataBit.isValid() && DataBit.toInt() > 0)
        SetInifile->setValue("SerialPort/DataBit",DataBit);
    if(StopBit.isValid() && !StopBit.toString().isEmpty())
        SetInifile->setValue("SerialPort/StopBit",StopBit);
    if(Parity.isValid() && !Parity.toString().isEmpty())
        SetInifile->setValue("SerialPort/Parity",Parity);
    if(User.isValid() && !User.toString().isEmpty())
        SetInifile->setValue("Mail/User",User);
    if(Password.isValid() && !Password.toString().isEmpty())
        SetInifile->setValue("Mail/Password",Password);
    if(SendAddr.isValid() && !SendAddr.toString().isEmpty())
        SetInifile->setValue("Mail/SendAddr",SendAddr);
    if(RecvAddr.isValid() && !RecvAddr.toString().isEmpty())
        SetInifile->setValue("Mail/RecvAddr",RecvAddr);
    if(ServerAddr.isValid() && !ServerAddr.toString().isEmpty())
        SetInifile->setValue("Mail/ServerAddr",ServerAddr);
    if(Port.isValid() && !Port.toString().isEmpty())
        SetInifile->setValue("Mail/Port",Port);
    if(FontFamily.isValid() && !FontFamily.toString().isEmpty())
        SetInifile->setValue("Font/FontFamily",FontFamily);
    delete SetInifile;
}

QVariant DataManager::ReadSerialportData(const QString &key) {
    if(key == "PortName")
        return PortName;
    if(key == "BaudRate")
        return BaudRate;
    if(key == "DataBit")
        return DataBit;
    if(key == "StopBit")
        return StopBit;
    if(key == "Parity")
        return Parity;
    return QVariant("");
}

void DataManager::WriteSerialportData(const QString &key, QVariant value) {
    if(key == "PortName") {
        PortName = value;
        return;
    }
    if(key == "BaudRate") {
        BaudRate = value;
        return;
    }
    if(key == "DataBit") {
        DataBit = value;
        return;
    }
    if(key == "StopBit") {
        StopBit = value;
        return;
    }
    if(key == "Parity") {
        Parity = value;
        return;
    }
}

QVariant DataManager::ReadMailData(const QString &key) {
    if(key == "User")
        return User;
    if(key == "Password")
        return Password;
    if(key == "SendAddr")
        return SendAddr;
    if(key == "RecvAddr")
        return RecvAddr;
    if(key == "ServerAddr")
        return ServerAddr;
    if(key == "Port")
        return Port;
}

void DataManager::WriteMailData(const QString &key, QVariant value) {
    if(key == "User") {
        User = value;
        return;
    }
    if(key == "Password") {
        Password = value;
        return;
    }
    if(key == "SendAddr") {
        SendAddr = value;
        return;
    }
    if(key == "RecvAddr") {
        RecvAddr = value;
        return;
    }
    if(key == "ServerAddr") {
        ServerAddr = value;
        return;
    }
    if(key == "Port") {
        Port = value;
        return;
    }
}

QVariant DataManager::ReadFontfamilyData() {
    return FontFamily;
}

void DataManager::WriteFontfamilyData(QVariant value) {
    FontFamily = value;
}

