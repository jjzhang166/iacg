#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVariant>
#include <QString>
#include <QSettings>
#include <QPair>
#include <QMessageBox>
#include <QDir>
#include <QUnhandledException>
#include <QObject>
#include <limits>

class DataManager
{
public:
    enum BootData {
        BOOT_SMTP,
        BOOT_SERIALPORT
    };

    enum SerialportData {
        SERIALPORT_PORTNAME,
        SERIALPORT_BAUDRATE,
        SERIALPORT_DATABITS,
        SERIALPORT_STOPBITS,
        SERIALPORT_PARITY
    };

    enum MailData {
        MAIL_USER,
        MAIL_PASSWORD,
        MAIL_SENDADDR,
        MAIL_RECVADDR,
        MAIL_SERVERADDR,
        MAIL_PORT
    };

    enum FrameData {
        FRAME_LEN,
        FRAME_HEADER,
        FRAME_HEADERLEN,
        FRAME_HUMI,
        FRAME_HUMILEN,
        FRAME_TEMP,
        FRAME_TEMPLEN,
        FRAME_LIGHT,
        FRAME_LIGHTLEN,
        SNDFRAME_HEADER,
        SNDFRAME_CHECK,
        SNDFRAME_UNCHEKC,
        SNDFRAME_BODY0,
        SNDFRAME_BODY1,
        SNDFRAME_BODY2,
        SNDFRAME_BODY3,
        SNDFRAME_BODY4
    };

    enum LightLevel {
        LL_HIGH,
        LL_MH,
        LL_MEDIUM,
        LL_LOW
    };

public:
    DataManager(const QString &filename);
    ~DataManager();

public:
    int parseLightLevel(const int lg);
    QVariant ReadFrameData(const FrameData key);

    QVariant ReadSerialportData(const SerialportData key);
    void WriteSerialportData(const SerialportData key, QVariant value);

    QVariant ReadFontfamilyData();
    void WriteFontfamilyData(QVariant value);

    QVariant ReadMailData(const MailData key);
    void WriteMailData(const MailData key, QVariant value);

    QVariant ReadBootData(const BootData key);
    void WriteBootData(const BootData key, QVariant value);

private:
    void initDataFrame(const QString &cfgfile="frame.ini");
    void saveDataFrame(const QString &cfgfile="frame.ini");

private:
    QSettings *SetInifile = nullptr;
    QString FileName;

    //串口相关数据
    QVariant PortName;
    QVariant BaudRate;
    QVariant DataBits;
    QVariant StopBits;
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

    //启动配置
    QVariant SmtpBoot;
    QVariant SerialportBoot;

    //数据帧配置
    QVariant frameLen;              //一帧的长度
    QVariant frameheader;           //一帧的头部
    QVariant frameheaderLen;        //一帧头的长度
    QVariant framehumi;             //湿度数据的位置
    QVariant framehumiLen;          //湿度数据的长度
    QVariant frametemp;             //温度数据的位置
    QVariant frametempLen;          //温度数据的长度
    QVariant framelight;            //光照数据的位置
    QVariant framelightLen;         //光照数据的长度
    QVariant framelight_Hvalue;     //高光照强度区间
    QVariant framelight_MHvalue;    //中高光照强度区间
    QVariant framelight_Mvalue;     //中等光照强度区间
    QVariant framelight_Lvalue;     //低光照强度区间

    QPair<int,int> h_lightSection;
    QPair<int,int> mh_lightSection;
    QPair<int,int> m_lightSection;
    QPair<int,int> l_lightSection;

    //控制帧配置
    QVariant sndframeheader;    //控制帧的头部
    QVariant sndframecheck;     //控制单片机自动补光时发送的数据
    QVariant sndframeuncheck;   //控制单片机不自动补光时发送的数据
    QVariant sndframebody_0;    //控制单片机补光级别0
    QVariant sndframebody_1;    //控制单片机补光级别1
    QVariant sndframebody_2;    //控制单片机补光级别2
    QVariant sndframebody_3;    //控制单片机补光级别3
    QVariant sndframebody_4;    //控制单片机补光级别4

};

#endif // DATAMANAGER_H
