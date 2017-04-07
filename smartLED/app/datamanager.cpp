#include "datamanager.h"
#include <QDebug>

DataManager::DataManager(const QString &filename)
    : FileName(filename) {
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    PortName = SetInifile->value("SerialPort/PortName");
    BaudRate = SetInifile->value("SerialPort/BaudRate");
    DataBits = SetInifile->value("SerialPort/DataBits");
    StopBits = SetInifile->value("SerialPort/StopBits");
    Parity = SetInifile->value("SerialPort/Parity");
    User = SetInifile->value("Mail/User");
    Password = SetInifile->value("Mail/Password");
    SendAddr = SetInifile->value("Mail/SendAddr");
    RecvAddr = SetInifile->value("Mail/RecvAddr");
    ServerAddr = SetInifile->value("Mail/ServerAddr");
    Port = SetInifile->value("Mail/Port");
    FontFamily = SetInifile->value("Font/FontFamily");
    SmtpBoot = SetInifile->value("Boot/SmtpBoot",QVariant(false));
    SerialportBoot = SetInifile->value("Boot/SerialportBoot",QVariant(true));
    delete SetInifile;
}

DataManager::~DataManager() {
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    if(PortName.isValid() && !PortName.toString().isEmpty())
        SetInifile->setValue("SerialPort/PortName", PortName);
    if(BaudRate.isValid() && BaudRate.toInt() > 0)
        SetInifile->setValue("SerialPort/BaudRate",BaudRate);
    if(DataBits.isValid() && DataBits.toInt() > 0)
        SetInifile->setValue("SerialPort/DataBits",DataBits);
    if(StopBits.isValid() && !StopBits.toString().isEmpty())
        SetInifile->setValue("SerialPort/StopBits",StopBits);
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
    if(SmtpBoot.isValid())
        SetInifile->setValue("Boot/SmtpBoot",SmtpBoot);
    if(SerialportBoot.isValid())
        SetInifile->setValue("Boot/SerialportBoot",SerialportBoot);
    delete SetInifile;
}

QVariant DataManager::ReadSerialportData(const SerialportData key) {
    switch(key) {
    case SERIALPORT_PORTNAME:
        return PortName;
        break;
    case SERIALPORT_BAUDRATE:
        return BaudRate;
        break;
    case SERIALPORT_DATABITS:
        return DataBits;
        break;
    case SERIALPORT_STOPBITS:
        return StopBits;
        break;
    case SERIALPORT_PARITY:
        return Parity;
        break;
    }
    return QVariant("");
}

void DataManager::WriteSerialportData(const SerialportData key, QVariant value) {
    switch(key) {
    case SERIALPORT_PORTNAME:
        PortName = value;
        break;
    case SERIALPORT_BAUDRATE:
        BaudRate = value;
        break;
    case SERIALPORT_DATABITS:
        DataBits = value;
        break;
    case SERIALPORT_STOPBITS:
        StopBits = value;
        break;
    case SERIALPORT_PARITY:
        Parity = value;
        break;
    }
}

QVariant DataManager::ReadMailData(const MailData key) {
    switch(key) {
    case MAIL_USER:
        return User;
        break;
    case MAIL_PASSWORD:
        return Password;
       break;
    case MAIL_SENDADDR:
        return SendAddr;
        break;
    case MAIL_RECVADDR:
        return RecvAddr;
        break;
    case MAIL_SERVERADDR:
        return ServerAddr;
        break;
    case MAIL_PORT:
        return Port;
        break;
    }
    return QVariant("");
}

void DataManager::WriteMailData(const MailData key, QVariant value) {
    switch(key) {
    case MAIL_USER:
        User = value;
        break;
    case MAIL_PASSWORD:
        Password = value;
       break;
    case MAIL_SENDADDR:
        SendAddr = value;
        break;
    case MAIL_RECVADDR:
        RecvAddr = value;
        break;
    case MAIL_SERVERADDR:
        ServerAddr = value;
        break;
    case MAIL_PORT:
        Port = value;
        break;
    }
}

QVariant DataManager::ReadFontfamilyData() {
    return FontFamily;
}

void DataManager::WriteFontfamilyData(QVariant value) {
    FontFamily = value;
}

QVariant DataManager::ReadBootData(const BootData key) {
    switch(key) {
    case BOOT_SMTP:
        return SmtpBoot;
        break;
    case BOOT_SERIALPORT:
        return SerialportBoot;
        break;
    }
}

void DataManager::WriteBootData(const BootData key, QVariant value) {
    switch(key) {
    case BOOT_SMTP:
        SmtpBoot = value;
        break;
    case BOOT_SERIALPORT:
        SerialportBoot = value;
        break;
    }
}
