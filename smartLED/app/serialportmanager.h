﻿#ifndef SERIALCONNECT_H
#define SERIALCONNECT_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "datamanager.h"

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
    void lightChanged(const QString &lg);

public:
    SerialportManager(DataManager *dm, QObject *parent = 0);
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
    /*
     * 名称：connectSart
     * 参数：无
     * 返回值：bool，指示是否成功
     * 作用：上位机尝试通过指定的串口与单片机进行通信
     */
    Q_INVOKABLE bool connectSart();
    /*
     * 名称：connectStop
     * 参数：无
     * 返回值：无
     * 作用：上位机停止与单片机的通信
     */
    Q_INVOKABLE void connectStop();

    //弃用
    Q_INVOKABLE void writeChar(const QString&);
    /*
     * 名称：writeByte
     * 参数：QString,要发送的数据帧，为string类型的
     * 十六进制字符串，如"ff","11","0f"
     * 返回值：无
     * 作用：向单片机发送指定十六进制数据帧，从而达到通过上位机控制
     * 单片机的效果
     */
    Q_INVOKABLE void writeByte(const QString&);

private:
    QSerialPort *linkPort;
    DataManager *dataManager;
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
    /*
     * 名称：QString2Hex
     * 参数：QString, 十六进制的字符串，如"ff","01"
     * 返回值：QByteArray，十六进制值
     * 作用：将十六进制字符串转换成能通过串口发送，单片机可以识别的
     * 十六进制值
     */
    QByteArray QString2Hex(QString str);
    //此方法为QString2Hex内部调用
    char ConvertHexChar(char ch);
};

#endif // SERIALCONNECT_H