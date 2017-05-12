/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/
#ifndef SERIALCONNECT_H
#define SERIALCONNECT_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>

class SerialportManager : public QObject {
    Q_OBJECT

    Q_ENUMS(QSerialPort::BaudRate)
    Q_ENUMS(QSerialPort::DataBits)
    Q_ENUMS(QSerialPort::StopBits)
    Q_ENUMS(QSerialPort::Parity)

    /*
     * 以下为serialConnet类的属性表
     * portName: 串口的名字
     * light: 搜集到的光照数据
     * temperature: 搜集到的温度数据
     * humidity: 搜集到的湿度数据
     * portList: 用于保存系统可能用到的串口名
     */
    Q_PROPERTY(QString portName READ portName WRITE setPortName)
    Q_PROPERTY(QSerialPort::BaudRate baudRate READ baudRate WRITE setBaudRate)
    Q_PROPERTY(QSerialPort::DataBits dataBits READ dataBits WRITE setDataBits)
    Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits)
    Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity)
    Q_PROPERTY(QString light READ light WRITE setLight)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature)
    Q_PROPERTY(QString humidity READ humidity WRITE setHumidity)
    Q_PROPERTY(QStringList portList READ portList CONSTANT)

signals:
    /*
     * 以下为类的信号声明:
     * tempChanged(const QString &tm) 温度改变时发送此信号
     * humiChanged(const QString &hm) 湿度改变时发送此信号
     * lightChanged(const QString &lg) 光照改变时发送此信号
     */
    void tempChanged(const QString &tm);
    void humiChanged(const QString &hm);
    void lightChanged(const int ll);

public:
    SerialportManager(QObject *parent = 0);
    ~SerialportManager();

public:
    QStringList portList() const;

    QString portName() const;
    void    setPortName(const QString &port_name);

    QSerialPort::BaudRate baudRate() const;
    void    setBaudRate(const QSerialPort::BaudRate br);

    QSerialPort::DataBits dataBits() const;
    void    setDataBits(const QSerialPort::DataBits db);

    QSerialPort::StopBits stopBits() const;
    void    setStopBits(const QSerialPort::StopBits sbt);

    QSerialPort::Parity parity() const;
    void    setParity(const QSerialPort::Parity p);

    QString light() const;
    void    setLight(const QString &lg);

    QString temperature() const;
    void    setTemperature(const QString &tem);

    QString humidity() const;
    void    setHumidity(const QString &hum);

    Q_INVOKABLE void refreshPortlist();
    Q_INVOKABLE void sndControlFrame(const bool checked, const int level);
    Q_INVOKABLE bool connectSart();
    Q_INVOKABLE void connectStop();

private:
    QSettings ini_setting;
    QSerialPort *linkPort;
    QSerialPort::BaudRate m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::Parity   m_parity;
    QString m_portName;
    QString m_light;
    QString m_temperature;
    QString m_humidity;
    QStringList m_portList;

private:
    void InitPortlist();

    //向单片机发送指定十六进制数据帧，从而达到通过上位机控制单片机的效果
    void writeByte(const QString&);

    //作用：将十六进制字符串转换成能通过串口发送，单片机可以识别的十六进制值
    QByteArray QString2Hex(QString str);

    //此方法为QString2Hex内部调用
    char ConvertHexChar(char ch);
};

#endif // SERIALCONNECT_H
