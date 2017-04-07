#include "serialportmanager.h"
#include <QDebug>

SerialportManager::SerialportManager(DataManager *dm, QObject *parent) :
    QObject(parent),
    dataManager(dm),
    m_baudRate(QSerialPort::BaudRate::Baud9600),
    m_dataBits(QSerialPort::DataBits::Data8),
    m_stopBits(QSerialPort::StopBits::OneStop),
    m_parity(QSerialPort::Parity::NoParity) {

    InitPortlist();

    QString pn = dm->ReadSerialportData(DataManager::SERIALPORT_PORTNAME).toString();
    if(!pn.isEmpty())
        m_portName = pn;
    bool ok;
    int res = dm->ReadSerialportData(DataManager::SERIALPORT_BAUDRATE).toInt(&ok);
    if(ok) m_baudRate = (QSerialPort::BaudRate)res;
    res = dm->ReadSerialportData(DataManager::SERIALPORT_DATABITS).toInt(&ok);
    if(ok) m_dataBits = (QSerialPort::DataBits)res;
    float sbit = dm->ReadSerialportData(DataManager::SERIALPORT_STOPBITS).toFloat(&ok);
    if(ok) {
       if(sbit == 1)
            m_stopBits = QSerialPort::OneStop;
        else if(sbit == 1.5)
            m_stopBits = QSerialPort::OneAndHalfStop;
        else if(sbit == 2)
            m_stopBits = QSerialPort::TwoStop;
    }
    pn = dm->ReadSerialportData(DataManager::SERIALPORT_PARITY).toString();
    if(!pn.isEmpty()) {
        if(pn.toLower() == "no")
            m_parity = QSerialPort::Parity::NoParity;
        else if(pn.toLower() == "odd")
            m_parity = QSerialPort::Parity::OddParity;
        else if(pn.toLower() == "even")
            m_parity = QSerialPort::Parity::EvenParity;
    }

    linkPort = new QSerialPort;
    QObject::connect(linkPort,&QSerialPort::readyRead,this,[=](){
         QByteArray data = linkPort->readAll();
         if(data.left(1).toHex() != "ff" || data.length() != 6)
             goto exit;
         this->m_humidity = data.mid(1,2).toHex();
         this->m_temperature = data.mid(3,2).toHex();
         this->m_light = data.right(1).toHex();
         emit humiChanged(m_humidity);
         emit tempChanged(m_temperature);
         emit lightChanged(m_light);
         exit:
         linkPort->clear();
    });
}

SerialportManager::~SerialportManager() {
    linkPort->close();
    dataManager->WriteSerialportData(DataManager::SERIALPORT_PORTNAME,QVariant(m_portName));
    dataManager->WriteSerialportData(DataManager::SERIALPORT_BAUDRATE,QVariant(m_baudRate).toInt());
    dataManager->WriteSerialportData(DataManager::SERIALPORT_DATABITS,QVariant(m_dataBits).toInt());
    if(m_stopBits == QSerialPort::OneStop)
        dataManager->WriteSerialportData(DataManager::SERIALPORT_STOPBITS,QVariant(1));
    else if(m_stopBits == QSerialPort::OneAndHalfStop)
        dataManager->WriteSerialportData(DataManager::SERIALPORT_STOPBITS,QVariant(1.5));
    else if(m_stopBits == QSerialPort::TwoStop)
        dataManager->WriteSerialportData(DataManager::SERIALPORT_STOPBITS,QVariant(2));

    switch (m_parity) {
    case QSerialPort::Parity::NoParity:
        dataManager->WriteSerialportData(DataManager::SERIALPORT_PARITY,QVariant("No"));
        break;
    case QSerialPort::Parity::OddParity:
        dataManager->WriteSerialportData(DataManager::SERIALPORT_PARITY,QVariant("Odd"));
        break;
    case QSerialPort::Parity::EvenParity:
        dataManager->WriteSerialportData(DataManager::SERIALPORT_PARITY,QVariant("Even"));
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

void SerialportManager::writeChar(const QString &cc) {
    char data = cc[0].cell();
    linkPort->clear();
    linkPort->write(&data);
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

