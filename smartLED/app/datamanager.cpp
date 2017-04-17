#include "datamanager.h"
#include <QDebug>

DataManager::DataManager(const QString &filename)
    : FileName(filename) {
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    Q_ASSERT(SetInifile != nullptr);
    PortName = SetInifile->value("SerialPort/PortName");
    BaudRate = SetInifile->value("SerialPort/BaudRate");
    DataBits = SetInifile->value("SerialPort/DataBits");
    StopBits = SetInifile->value("SerialPort/StopBits");
    Parity = SetInifile->value("SerialPort/Parity");
    User = SetInifile->value("Mail/User");
    Password = SetInifile->value("Mail/Password");
    SendAddr = SetInifile->value("Mail/SendAddr");
    RecvAddr = SetInifile->value("Mail/RecvAddr");
    ServerAddr = SetInifile->value("Mail/ServerAddr");
    Port = SetInifile->value("Mail/Port");
    FontFamily = SetInifile->value("Font/FontFamily");
    SmtpBoot = SetInifile->value("Boot/SmtpBoot",QVariant(false));
    SerialportBoot = SetInifile->value("Boot/SerialportBoot",QVariant(true));
    delete SetInifile;
    initDataFrame();
}

DataManager::~DataManager() {
    qDebug() << "destroy data manager";
    SetInifile = new QSettings(FileName,QSettings::IniFormat);
    Q_ASSERT(SetInifile != nullptr);
    if(PortName.isValid() && !PortName.toString().isEmpty())
        SetInifile->setValue("SerialPort/PortName", PortName);
    if(BaudRate.isValid() && BaudRate.toInt() > 0)
        SetInifile->setValue("SerialPort/BaudRate",BaudRate);
    if(DataBits.isValid() && DataBits.toInt() > 0)
        SetInifile->setValue("SerialPort/DataBits",DataBits);
    if(StopBits.isValid() && !StopBits.toString().isEmpty())
        SetInifile->setValue("SerialPort/StopBits",StopBits);
    if(Parity.isValid() && !Parity.toString().isEmpty())
        SetInifile->setValue("SerialPort/Parity",Parity);
    if(User.isValid() && !User.toString().isEmpty())
        SetInifile->setValue("Mail/User",User);
    if(Password.isValid() && !Password.toString().isEmpty())
        SetInifile->setValue("Mail/Password",Password);
    if(SendAddr.isValid() && !SendAddr.toString().isEmpty())
        SetInifile->setValue("Mail/SendAddr",SendAddr);
    if(RecvAddr.isValid() && !RecvAddr.toString().isEmpty())
        SetInifile->setValue("Mail/RecvAddr",RecvAddr);
    if(ServerAddr.isValid() && !ServerAddr.toString().isEmpty())
        SetInifile->setValue("Mail/ServerAddr",ServerAddr);
    if(Port.isValid() && !Port.toString().isEmpty())
        SetInifile->setValue("Mail/Port",Port);
    if(FontFamily.isValid() && !FontFamily.toString().isEmpty())
        SetInifile->setValue("Font/FontFamily",FontFamily);
    if(SmtpBoot.isValid())
        SetInifile->setValue("Boot/SmtpBoot",SmtpBoot);
    if(SerialportBoot.isValid())
        SetInifile->setValue("Boot/SerialportBoot",SerialportBoot);
    delete SetInifile;
    saveDataFrame();
}

void DataManager::initDataFrame(const QString &cfgfile) {
    SetInifile = new QSettings(cfgfile, QSettings::IniFormat);
    if(!QDir::current().exists(cfgfile)) {
        if(!QDir::current().exists("frameCreator.exe")) {
           int stdbutton =
                   QMessageBox::warning(nullptr, QObject::tr("warning"), QObject::tr("file:'frame.ini' is not exist.\n"
                                                          "use default frame config?"), QMessageBox::Yes,QMessageBox::No);
            if(stdbutton == (int)QMessageBox::No)
                throw new QUnhandledException;
        }
        else {
            int stdbutton =
                    QMessageBox::warning(nullptr, QObject::tr("warning"), QObject::tr("file:'frame.ini' is not exist.\n"
                                                           "crate a new file?"), QMessageBox::Yes, QMessageBox::No);
            if(stdbutton == (int)QMessageBox::Yes) {
                QProcess fc;
                fc.startDetached(QDir::currentPath() + "/frameCreator.exe");
                throw new QUnhandledException;
            }
        }
    }
    Q_ASSERT(SetInifile != nullptr);
    frameLen = SetInifile->value("DataFrame/FrameLen", 6);
    frameheader = SetInifile->value("DataFrame/FrameHeader", "ff");
    frameheaderLen = SetInifile->value("DataFrame/FrameHeaderLen", 1);
    framehumi = SetInifile->value("DataFrame/FrameHumi", 1);
    framehumiLen = SetInifile->value("DataFrame/FrameHumiLen", 2);
    frametemp = SetInifile->value("DataFrame/FrameTemp", 3);
    frametempLen = SetInifile->value("DataFrame/FrameTempLen", 2);
    framelight = SetInifile->value("DataFrame/FrameLight", 5);
    framelightLen = SetInifile->value("DataFrame/FrameLightLen", 1);
    framelight_Hvalue = SetInifile->value("DataFrame/LightValue_H", "-1|100");
    framelight_MHvalue = SetInifile->value("DataFrame/LightValue_MH", "100|140");
    framelight_Mvalue = SetInifile->value("DataFrame/LightValue_M", "140|230");
    framelight_Lvalue = SetInifile->value("DataFrame/LightValue_L", "230|-1");
    //控制帧配置初始化
    sndframeheader = SetInifile->value("ControlFrame/FrameHeader", "ff");
    sndframecheck = SetInifile->value("ControlFrame/FrameCheck", "01");
    sndframeuncheck = SetInifile->value("ControlFrame/FrameUnCheck", "00");
    sndframebody_0 = SetInifile->value("ControlFrame/FrameBody_0", "00");
    sndframebody_1 = SetInifile->value("ControlFrame/FrameBody_1", "0a");
    sndframebody_2 = SetInifile->value("ControlFrame/FrameBody_2", "14");
    sndframebody_3 = SetInifile->value("ControlFrame/FrameBody_3", "1e");
    sndframebody_4 = SetInifile->value("ControlFrame/FrameBody_4", "28");
    delete SetInifile;

    QString lightdata = framelight_Hvalue.toString();
    int pos = lightdata.indexOf('|');
    h_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());
    if(h_lightSection.first == -1)
        h_lightSection.first = INT_MIN;
    else if(h_lightSection.second == -1)
        h_lightSection.second = INT_MAX;

    lightdata = framelight_MHvalue.toString();
    pos = lightdata.indexOf('|');
    mh_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());

    lightdata = framelight_Mvalue.toString();
    pos = lightdata.indexOf('|');
    m_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());

    lightdata = framelight_Lvalue.toString();
    pos = lightdata.indexOf('|');
    l_lightSection = qMakePair(lightdata.mid(0, pos).toInt(), lightdata.mid(pos+1).toInt());
    if(l_lightSection.first == -1)
        l_lightSection.first = INT_MIN;
    else if(l_lightSection.second == -1)
        l_lightSection.second = INT_MAX;
}

void DataManager::saveDataFrame(const QString &cfgfile) {
    SetInifile = new QSettings(cfgfile, QSettings::IniFormat);
    Q_ASSERT(SetInifile != nullptr);
    SetInifile->setValue("DataFrame/FrameLen", frameLen);
    SetInifile->setValue("DataFrame/FrameHeader", frameheader);
    SetInifile->setValue("DataFrame/FrameHeaderLen", frameheaderLen);
    SetInifile->setValue("DataFrame/FrameHumi", framehumi);
    SetInifile->setValue("DataFrame/FrameHumiLen", framehumiLen);
    SetInifile->setValue("DataFrame/FrameTemp", frametemp);
    SetInifile->setValue("DataFrame/FrameTempLen", frametempLen);
    SetInifile->setValue("DataFrame/FrameLight", framelight);
    SetInifile->setValue("DataFrame/FrameLightLen", framelightLen);
    SetInifile->setValue("DataFrame/LightValue_H", framelight_Hvalue);
    SetInifile->setValue("DataFrame/LightValue_MH", framelight_MHvalue);
    SetInifile->setValue("DataFrame/LightValue_M", framelight_Mvalue);
    SetInifile->setValue("DataFrame/LightValue_L", framelight_Lvalue);
    //控制帧配置保存
    SetInifile->setValue("ControlFrame/FrameHeader", sndframeheader);
    SetInifile->setValue("ControlFrame/FrameCheck", sndframecheck);
    SetInifile->setValue("ControlFrame/FrameUnCheck", sndframeuncheck);
    SetInifile->setValue("ControlFrame/FrameBody_0", sndframebody_0);
    SetInifile->setValue("ControlFrame/FrameBody_1", sndframebody_1);
    SetInifile->setValue("ControlFrame/FrameBody_2", sndframebody_2);
    SetInifile->setValue("ControlFrame/FrameBody_3", sndframebody_3);
    SetInifile->setValue("ControlFrame/FrameBody_4", sndframebody_4);
    delete SetInifile;
}

QVariant DataManager::ReadFrameData(const FrameData key) {
    switch (key) {
    case FRAME_LEN:
        return frameLen;
        break;
    case FRAME_HEADER:
        return frameheader;
        break;
    case FRAME_HEADERLEN:
        return frameheaderLen;
        break;
    case FRAME_HUMI:
        return framehumi;
        break;
    case FRAME_HUMILEN:
        return framehumiLen;
        break;
    case FRAME_TEMP:
        return frametemp;
        break;
    case FRAME_TEMPLEN:
        return frametempLen;
        break;
    case FRAME_LIGHT:
        return framelight;
        break;
    case FRAME_LIGHTLEN:
        return framelightLen;
        break;
    case SNDFRAME_HEADER:
        return sndframeheader;
        break;
    case SNDFRAME_CHECK:
        return sndframecheck;
        break;
    case SNDFRAME_UNCHEKC:
        return sndframeuncheck;
    case SNDFRAME_BODY0:
        return sndframebody_0;
        break;
    case SNDFRAME_BODY1:
        return sndframebody_1;
        break;
    case SNDFRAME_BODY2:
        return sndframebody_2;
        break;
    case SNDFRAME_BODY3:
        return sndframebody_3;
        break;
    case SNDFRAME_BODY4:
        return sndframebody_4;
        break;
    }
    return QVariant("");
}

int DataManager::parseLightLevel(const int lg) {
    if(h_lightSection.first < lg && lg < h_lightSection.second)
        return LL_HIGH;
    if(mh_lightSection.first < lg && lg < mh_lightSection.second)
        return LL_MH;
    if(m_lightSection.first < lg && lg < m_lightSection.second)
        return LL_MEDIUM;
    if(l_lightSection.first < lg && lg < l_lightSection.second)
        return LL_LOW;
    return -1;      //parse error
}

QVariant DataManager::ReadSerialportData(const SerialportData key) {
    switch(key) {
    case SERIALPORT_PORTNAME:
        return PortName;
        break;
    case SERIALPORT_BAUDRATE:
        return BaudRate;
        break;
    case SERIALPORT_DATABITS:
        return DataBits;
        break;
    case SERIALPORT_STOPBITS:
        return StopBits;
        break;
    case SERIALPORT_PARITY:
        return Parity;
        break;
    }
    return QVariant("");
}

void DataManager::WriteSerialportData(const SerialportData key, QVariant value) {
    switch(key) {
    case SERIALPORT_PORTNAME:
        PortName = value;
        break;
    case SERIALPORT_BAUDRATE:
        BaudRate = value;
        break;
    case SERIALPORT_DATABITS:
        DataBits = value;
        break;
    case SERIALPORT_STOPBITS:
        StopBits = value;
        break;
    case SERIALPORT_PARITY:
        Parity = value;
        break;
    }
}

QVariant DataManager::ReadMailData(const MailData key) {
    switch(key) {
    case MAIL_USER:
        return User;
        break;
    case MAIL_PASSWORD:
        return Password;
       break;
    case MAIL_SENDADDR:
        return SendAddr;
        break;
    case MAIL_RECVADDR:
        return RecvAddr;
        break;
    case MAIL_SERVERADDR:
        return ServerAddr;
        break;
    case MAIL_PORT:
        return Port;
        break;
    }
    return QVariant("");
}

void DataManager::WriteMailData(const MailData key, QVariant value) {
    switch(key) {
    case MAIL_USER:
        User = value;
        break;
    case MAIL_PASSWORD:
        Password = value;
       break;
    case MAIL_SENDADDR:
        SendAddr = value;
        break;
    case MAIL_RECVADDR:
        RecvAddr = value;
        break;
    case MAIL_SERVERADDR:
        ServerAddr = value;
        break;
    case MAIL_PORT:
        Port = value;
        break;
    }
}

QVariant DataManager::ReadFontfamilyData() {
    return FontFamily;
}

void DataManager::WriteFontfamilyData(QVariant value) {
    FontFamily = value;
}

QVariant DataManager::ReadBootData(const BootData key) {
    switch(key) {
    case BOOT_SMTP:
        return SmtpBoot;
        break;
    case BOOT_SERIALPORT:
        return SerialportBoot;
        break;
    }
    return QVariant("");
}

void DataManager::WriteBootData(const BootData key, QVariant value) {
    switch(key) {
    case BOOT_SMTP:
        SmtpBoot = value;
        break;
    case BOOT_SERIALPORT:
        SerialportBoot = value;
        break;
    }
}
