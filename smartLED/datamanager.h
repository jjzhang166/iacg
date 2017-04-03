#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVariant>
#include <QString>
#include <QSettings>

class DataManager
{
public:
    DataManager(const QString &filename);
    ~DataManager();

public:
    QVariant ReadSerialportData(const QString &key);
    void WriteSerialportData(const QString &key, QVariant value);

    QVariant ReadFontfamilyData();
    void WriteFontfamilyData(QVariant value);

    QVariant ReadMailData(const QString &key);
    void WriteMailData(const QString &key, QVariant value);

private:
    QSettings *SetInifile = nullptr;
    QString FileName;

    //串口相关数据
    QVariant PortName;
    QVariant BaudRate;
    QVariant DataBit;
    QVariant StopBit;
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
};

#endif // DATAMANAGER_H
