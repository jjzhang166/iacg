#include "serialconnect.h"
#include <QDebug>

serialConnect::serialConnect(QObject *parent) : QObject(parent) {
    linkPort = new QSerialPort;
    QObject::connect(linkPort,&QSerialPort::readyRead,this,[=](){
         QByteArray data = linkPort->readAll();
         if(data.left(1).toHex() != "ff" || data.length() != 6)
             goto exit;
         this->m_humidity = data.mid(1,2).toHex();
         this->m_temperature = data.mid(3,2).toHex();
         this->m_light = data.right(1).toHex();
         emit dataChanged(this->m_light,this->m_temperature,this->m_humidity);
         //qDebug() << "light:" << this->m_light;
         //qDebug() << "temperature:" << this->m_temperature;
         //qDebug() << "humidity:" << this->m_humidity;
         exit:
         linkPort->clear();
    });
}

serialConnect::~serialConnect() {

}

void serialConnect::writeChar(const QString &cc) {
    char data = cc[0].cell();
    linkPort->clear();
    linkPort->write(&data);
}

void serialConnect::writeByte(const QString &b) {
    QByteArray data = QString2Hex(b);
    linkPort->clear();
    linkPort->write(data);
}

bool serialConnect::connectSart() {
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

void serialConnect::connectStop() {
    linkPort->close();
}

QString serialConnect::portName() const {
    return this->m_portName;
}

void serialConnect::setPortName(const QString &port_name) {
    this->m_portName = port_name;
}

QString serialConnect::light() const {
    return this->m_light;
}

void serialConnect::setLight(const QString &lg) {
    this->m_light = lg;
}

QString serialConnect::temperature() const {
    return this->m_temperature;
}

void serialConnect::setTemperature(const QString &tem) {
    this->m_temperature = tem;
}

QString serialConnect::humidity() const {
    return this->m_humidity;
}

void serialConnect::setHumidity(const QString &hum) {
    this->m_humidity = hum;
}

QSerialPort::BaudRate serialConnect::baudRate() const {
    return this->m_baudRate;
}

void serialConnect::setBaudRate(const int br) {
    this->m_baudRate = (QSerialPort::BaudRate)br;
}

QSerialPort::DataBits serialConnect::dataBits() const {
    return this->m_dataBits;
}

void serialConnect::setDataBits(const int db) {
    this->m_dataBits = (QSerialPort::DataBits)db;
}

QSerialPort::StopBits serialConnect::stopBits() const {
    return this->m_stopBits;
}

void serialConnect::setStopBits(const int stb) {
    this->m_stopBits = (QSerialPort::StopBits)stb;
}

QSerialPort::Parity serialConnect::parity() const {
    return this->m_parity;
}

void serialConnect::setParity(const int sp) {
    this->m_parity = (QSerialPort::Parity)sp;
}

QByteArray serialConnect::QString2Hex(QString str) {
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

char serialConnect::ConvertHexChar(char ch) {
    if((ch >= '0') && (ch <= '9'))
                return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else
        return (-1);
}
