#include "serialportmanager.h"
#include <QUnhandledException>
#include <limits>
#include <QDebug>

SerialportManager::SerialportManager(QObject *parent) :
    QObject(parent),
    ini_setting("cfg.ini", QSettings::IniFormat),
    frame_setting("frame.ini", QSettings::IniFormat),
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
    QObject::connect(linkPort,&QSerialPort::readyRead,this,[=](){
         QByteArray data = linkPort->readAll();
         if(data.left(frameheaderLen).toHex() != frameheader || data.length() != frameLen)
             goto exit;
         this->m_humidity = data.mid(framehumi,framehumiLen).toHex();
         this->m_temperature = data.mid(frametemp,frametempLen).toHex();
         this->m_light = data.mid(framelight,framelightLen).toHex();
         LightLevel lightlevel = parseLightLevel(m_light.toInt(nullptr,16));
         emit humiChanged(m_humidity);
         emit tempChanged(m_temperature);
         emit lightChanged(lightlevel);
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

    frame_setting.setValue("DataFrame/FrameLen", frameLen);
    frame_setting.setValue("DataFrame/FrameHeader", QString(frameheader));
    frame_setting.setValue("DataFrame/FrameHeaderLen", frameheaderLen);
    frame_setting.setValue("DataFrame/FrameHumi", framehumi);
    frame_setting.setValue("DataFrame/FrameHumiLen", framehumiLen);
    frame_setting.setValue("DataFrame/FrameTemp", frametemp);
    frame_setting.setValue("DataFrame/FrameTempLen", frametempLen);
    frame_setting.setValue("DataFrame/FrameLight", framelight);
    frame_setting.setValue("DataFrame/FrameLightLen", framelightLen);
    frame_setting.setValue("DataFrame/LightValue_H", framelight_Hvalue);
    frame_setting.setValue("DataFrame/LightValue_MH", framelight_MHvalue);
    frame_setting.setValue("DataFrame/LightValue_M", framelight_Mvalue);
    frame_setting.setValue("DataFrame/LightValue_L", framelight_Lvalue);
    //控制帧配置保存
    frame_setting.setValue("ControlFrame/FrameHeader", QString(sndframeheader));
    frame_setting.setValue("ControlFrame/FrameCheck", QString(sndframecheck));
    frame_setting.setValue("ControlFrame/FrameUnCheck", QString(sndframeuncheck));
    frame_setting.setValue("ControlFrame/FrameBody_0", QString(sndframebody_0));
    frame_setting.setValue("ControlFrame/FrameBody_1", QString(sndframebody_1));
    frame_setting.setValue("ControlFrame/FrameBody_2", QString(sndframebody_2));
    frame_setting.setValue("ControlFrame/FrameBody_3", QString(sndframebody_3));
    frame_setting.setValue("ControlFrame/FrameBody_4", QString(sndframebody_4));
}

SerialportManager::LightLevel SerialportManager::parseLightLevel(const int lg) {
    if(h_lightSection.first < lg && lg < h_lightSection.second)
        return LL_HIGH;
    if(mh_lightSection.first < lg && lg < mh_lightSection.second)
        return LL_MH;
    if(m_lightSection.first < lg && lg < m_lightSection.second)
        return LL_MEDIUM;
    if(l_lightSection.first < lg && lg < l_lightSection.second)
        return LL_LOW;
    return LL_ERROR;      //parse error
}

bool SerialportManager::parseLightSection() {
    QString lightdata = framelight_Hvalue;
    int pos = lightdata.indexOf('|');
    if(pos == -1) return false;
    h_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());
    if(h_lightSection.first == -1)
        h_lightSection.first = INT_MIN;
    else if(h_lightSection.second == -1)
        h_lightSection.second = INT_MAX;

    lightdata = framelight_MHvalue;
    pos = lightdata.indexOf('|');
    if(pos == - 1) return false;
    mh_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());

    lightdata = framelight_Mvalue;
    pos = lightdata.indexOf('|');
    if(pos == -1) return false;
    m_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());

    lightdata = framelight_Lvalue;
    pos = lightdata.indexOf('|');
    if(pos == -1) return false;

    l_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());
    if(l_lightSection.first == -1)
        l_lightSection.first = INT_MIN;
    else if(l_lightSection.second == -1)
        l_lightSection.second = INT_MAX;

    return true;
}

void SerialportManager::InitPortlist() {
    frameLen = frame_setting.value("DataFrame/FrameLen", 6).toInt();
    frameheader = frame_setting.value("DataFrame/FrameHeader", "ff").toByteArray();
    frameheaderLen = frame_setting.value("DataFrame/FrameHeaderLen", 1).toInt();
    framehumi = frame_setting.value("DataFrame/FrameHumi", 1).toInt();
    framehumiLen = frame_setting.value("DataFrame/FrameHumiLen", 2).toInt();
    frametemp = frame_setting.value("DataFrame/FrameTemp", 3).toInt();
    frametempLen = frame_setting.value("DataFrame/FrameTempLen", 2).toInt();
    framelight = frame_setting.value("DataFrame/FrameLight", 5).toInt();
    framelightLen = frame_setting.value("DataFrame/FrameLightLen", 1).toInt();
    framelight_Hvalue = frame_setting.value("DataFrame/LightValue_H", "-1|100").toString();
    framelight_MHvalue = frame_setting.value("DataFrame/LightValue_MH", "100|140").toString();
    framelight_Mvalue = frame_setting.value("DataFrame/LightValue_M", "140|230").toString();
    framelight_Lvalue = frame_setting.value("DataFrame/LightValue_L", "230|-1").toString();
    if(!parseLightSection()) throw new QUnhandledException;

    //控制帧配置初始化
    sndframeheader = frame_setting.value("ControlFrame/FrameHeader", "ff").toByteArray();
    sndframecheck = frame_setting.value("ControlFrame/FrameCheck", "01").toByteArray();
    sndframeuncheck = frame_setting.value("ControlFrame/FrameUnCheck", "00").toByteArray();
    sndframebody_0 = frame_setting.value("ControlFrame/FrameBody_0", "00").toByteArray();
    sndframebody_1 = frame_setting.value("ControlFrame/FrameBody_1", "0a").toByteArray();
    sndframebody_2 = frame_setting.value("ControlFrame/FrameBody_2", "14").toByteArray();
    sndframebody_3 = frame_setting.value("ControlFrame/FrameBody_3", "1e").toByteArray();
    sndframebody_4 = frame_setting.value("ControlFrame/FrameBody_4", "28").toByteArray();

    foreach (QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        m_portList.push_back(port.portName());
    }
    if(!m_portList.isEmpty())
        m_portName = m_portList.at(0);
    else
        m_portName = "";
}

void SerialportManager::sndControlFrame(const bool checked, const int level) {
    QString controlFrame = sndframeheader;
    if(checked)
        controlFrame += sndframecheck;
    else
        controlFrame += sndframeuncheck;
    switch(level) {
    case 0:
        controlFrame += sndframebody_0;
        break;
    case 1:
        controlFrame += sndframebody_1;
        break;
    case 2:
        controlFrame += sndframebody_2;
        break;
    case 3:
        controlFrame += sndframebody_3;
        break;
    case 4:
        controlFrame += sndframebody_4;
        break;
    }
    writeByte(controlFrame);
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

