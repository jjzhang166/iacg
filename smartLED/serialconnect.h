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
    Q_PROPERTY(QString light READ light WRITE setLight)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature)
    Q_PROPERTY(QString humidity READ humidity WRITE setHumidity)
    Q_PROPERTY(QStringList portList READ portList NOTIFY portListChanged)

signals:
    void portNameChanged(const QString &port_name);
    void tempChanged(const QString &tm);
    void humiChanged(const QString &hm);
    void lightChanged(const QString &lg);
    void portListChanged();
public:
    serialConnect(QObject *parent = 0);
    ~serialConnect();

public:
    QStringList portList() const;

    QString portName() const;
    void    setPortName(const QString &port_name);

    QString light() const;
    void    setLight(const QString &lg);

    QString temperature() const;
    void    setTemperature(const QString &tem);

    QString humidity() const;
    void    setHumidity(const QString &hum);

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

    Q_INVOKABLE void writeChar(const QString&);
    Q_INVOKABLE void writeByte(const QString&);

private:
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
    QByteArray QString2Hex(QString str);
    char ConvertHexChar(char ch);
};

#endif // SERIALCONNECT_H
