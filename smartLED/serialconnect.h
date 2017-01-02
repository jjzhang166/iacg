#ifndef SERIALCONNECT_H
#define SERIALCONNECT_H
#include <QObject>
#include <QSerialPort>

class serialConnect : public QObject {
    Q_OBJECT
    Q_ENUMS(QSerialPort::DataBits)
    Q_ENUMS(QSerialPort::BaudRate)
    Q_ENUMS(QSerialPort::StopBits)
    Q_ENUMS(QSerialPort::Parity)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)

signals:
    void portNameChanged(const QString &port_name);

public:
    serialConnect(QObject *parent = 0);
    ~serialConnect();

public:
    QString portName() const;
    void    setPortName(const QString &port_name);

    Q_INVOKABLE bool connectSart();
    Q_INVOKABLE void connectStop();

    Q_INVOKABLE QSerialPort::BaudRate baudRate() const;
    Q_INVOKABLE void setBaudRate(const int);

    Q_INVOKABLE QSerialPort::DataBits dataBits() const;
    Q_INVOKABLE void setDataBits(const int);

    Q_INVOKABLE QSerialPort::StopBits stopBits() const;
    Q_INVOKABLE void setStopBits(const int);

    Q_INVOKABLE QSerialPort::Parity parity() const;
    Q_INVOKABLE void setParity(const int);

    //test method
    Q_INVOKABLE void writeChar(const QString&);
    Q_INVOKABLE void writeByte(const QString&);

private:
    QSerialPort *linkPort;
    QSerialPort::BaudRate m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::Parity   m_parity;
    QString m_portName;

private:
    QByteArray QString2Hex(QString str);
    char ConvertHexChar(char ch);
};

#endif // SERIALCONNECT_H
