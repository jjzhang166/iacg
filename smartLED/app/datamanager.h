#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVariant>
#include <QString>
#include <QSettings>

class DataManager
{
public:
    enum BootData {
        BOOT_SMTP,
        BOOT_SERIALPORT
    };

    enum SerialportData {
        SERIALPORT_PORTNAME,
        SERIALPORT_BAUDRATE,
        SERIALPORT_DATABITS,
        SERIALPORT_STOPBITS,
        SERIALPORT_PARITY
    };

    enum MailData {
        MAIL_USER,
        MAIL_PASSWORD,
        MAIL_SENDADDR,
        MAIL_RECVADDR,
        MAIL_SERVERADDR,
        MAIL_PORT
    };

public:
    DataManager(const QString &filename);
    ~DataManager();

public:
    QVariant ReadSerialportData(const SerialportData key);
    void WriteSerialportData(const SerialportData key, QVariant value);

    QVariant ReadFontfamilyData();
    void WriteFontfamilyData(QVariant value);

    QVariant ReadMailData(const MailData key);
    void WriteMailData(const MailData key, QVariant value);

    QVariant ReadBootData(const BootData key);
    void WriteBootData(const BootData key, QVariant value);

private:
    QSettings *SetInifile = nullptr;
    QString FileName;

    //串口相关数据
    QVariant PortName;
    QVariant BaudRate;
    QVariant DataBits;
    QVariant StopBits;
    QVariant Parity;

    //邮箱配置
    QVariant User;
    QVariant Password;
    QVariant SendAddr;
    QVariant RecvAddr;
    QVariant ServerAddr;
    QVariant Port;

    //字体配置
    QVariant FontFamily;

    //启动配置
    QVariant SmtpBoot;
    QVariant SerialportBoot;

};

#endif // DATAMANAGER_H
