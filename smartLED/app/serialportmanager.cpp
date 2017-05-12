#include "serialportmanager.h"
#include "frame.h"
#include <QUnhandledException>
#include <QDebug>

SerialportManager::SerialportManager(QObject *parent) :
    QObject(parent),
    ini_setting("cfg.ini", QSettings::IniFormat),
    m_baudRate(QSerialPort::BaudRate::Baud9600),
    m_dataBits(QSerialPort::DataBits::Data8),
    m_stopBits(QSerialPort::StopBits::OneStop),
    m_parity(QSerialPort::Parity::NoParity) {

    InitPortlist();

    m_portName = ini_setting.value("SerialPort/PortName", "").toString();

    bool ok;
    m_baudRate = (QSerialPort::BaudRate)ini_setting.value("SerialPort/BaudRate", "9600").toInt(&ok);
    if(!ok) throw new QUnhandledException;
    m_dataBits = (QSerialPort::DataBits)ini_setting.value("SerialPort/DataBits", "8").toInt(&ok);
    if(!ok) throw new QUnhandledException;
    float sbit = ini_setting.value("SerialPort/StopBits", "1").toFloat(&ok);
    if(ok) {
       if(sbit == 1)
            m_stopBits = QSerialPort::OneStop;
        else if(sbit == 1.5)
            m_stopBits = QSerialPort::OneAndHalfStop;
        else if(sbit == 2)
            m_stopBits = QSerialPort::TwoStop;
    }
    else
        throw new QUnhandledException;
    QString pn = ini_setting.value("SerialPort/Parity", "no").toString();
    if(pn.toLower() == "no")
        m_parity = QSerialPort::Parity::NoParity;
    else if(pn.toLower() == "odd")
        m_parity = QSerialPort::Parity::OddParity;
    else if(pn.toLower() == "even")
        m_parity = QSerialPort::Parity::EvenParity;
    else
        throw new QUnhandledException;

    linkPort = new QSerialPort;
    QObject::connect(linkPort, &QSerialPort::readyRead, this, [=](){
         QByteArray data = linkPort->readAll();
         Frame dataframe(data);
         if(!dataframe.ok) goto exit;
         emit humiChanged(dataframe.getHumidity());
         emit tempChanged(dataframe.getTemperature());
         emit lightChanged(dataframe.getLightLevel());
         exit:
         linkPort->clear();
    });
}

SerialportManager::~SerialportManager() {
#ifdef QT_DEBUG
    qDebug() << "destroy serialport manager";
#endif
    linkPort->close();
    if(!m_portName.isEmpty()) ini_setting.setValue("SerialPort/PortName", m_portName);
    ini_setting.setValue("SerialPort/BaudRate", m_baudRate);
    ini_setting.setValue("SerialPort/DataBits", m_dataBits);
    if(m_stopBits == QSerialPort::OneStop)
        ini_setting.setValue("SerialPort/StopBits", 1);
    else if(m_stopBits == QSerialPort::OneAndHalfStop)
        ini_setting.setValue("SerialPort/StopBits", 1.5);
    else if(m_stopBits == QSerialPort::TwoStop)
        ini_setting.setValue("SerialPort/StopBits", 2);

    switch (m_parity) {
    case QSerialPort::Parity::NoParity:
        ini_setting.setValue("SerialPort/Parity", "No");
        break;
    case QSerialPort::Parity::OddParity:
        ini_setting.setValue("SerialPort/Parity", "Odd");
        break;
    case QSerialPort::Parity::EvenParity:
        ini_setting.setValue("SerialPort/Parity", "Even");
    }
}

void SerialportManager::InitPortlist() {
    foreach (QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        m_portList.push_back(port.portName());
    }
    if(!m_portList.isEmpty())
        m_portName = m_portList.at(0);
    else
        m_portName = "";
}

void SerialportManager::refreshPortlist() {
    m_portList.clear();
    InitPortlist();
}

void SerialportManager::sndControlFrame(const bool checked, const int level) {
    writeByte(Frame::getControlFrame(checked, level));
}

void SerialportManager::writeByte(const QString &b) {
    QByteArray data = QString2Hex(b);
    linkPort->clear();
    linkPort->write(data);
}

bool SerialportManager::connectSart() {
    linkPort->setPortName(m_portName);
    if(linkPort->open(QIODevice::ReadWrite)) {
        linkPort->setBaudRate(m_baudRate);
        linkPort->setDataBits(m_dataBits);
        linkPort->setStopBits(m_stopBits);
        linkPort->setParity(m_parity);
        linkPort->setFlowControl(QSerialPort::NoFlowControl);
        linkPort->clear();
        return true;
    }
    else
        return false;
}

void SerialportManager::connectStop() {
    linkPort->close();
}

QStringList SerialportManager::portList() const {
    return this->m_portList;
}

QString SerialportManager::portName() const {
    return this->m_portName;
}

void SerialportManager::setPortName(const QString &port_name) {
    this->m_portName = port_name;
}

QSerialPort::BaudRate SerialportManager::baudRate() const {
    return this->m_baudRate;
}

void SerialportManager::setBaudRate(const QSerialPort::BaudRate br) {
    this->m_baudRate = br;
}

QSerialPort::DataBits SerialportManager::dataBits() const {
    return this->m_dataBits;
}

void SerialportManager::setDataBits(const QSerialPort::DataBits db) {
    this->m_dataBits = db;
}

QSerialPort::StopBits SerialportManager::stopBits() const {
    return this->m_stopBits;
}

void SerialportManager::setStopBits(const QSerialPort::StopBits sbt) {
    this->m_stopBits = sbt;
}

QSerialPort::Parity SerialportManager::parity() const {
    return this->m_parity;
}

void SerialportManager::setParity(const QSerialPort::Parity p) {
    this->m_parity = p;
}

QString SerialportManager::light() const {
    return this->m_light;
}

void SerialportManager::setLight(const QString &lg) {
    this->m_light = lg;
}

QString SerialportManager::temperature() const {
    return this->m_temperature;
}

void SerialportManager::setTemperature(const QString &tem) {
    this->m_temperature = tem;
}

QString SerialportManager::humidity() const {
    return this->m_humidity;
}

void SerialportManager::setHumidity(const QString &hum) {
    this->m_humidity = hum;
}

QByteArray SerialportManager::QString2Hex(QString str) {
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

char SerialportManager::ConvertHexChar(char ch) {
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else
        return (-1);
}
