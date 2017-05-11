#include "frame.h"
#include <QMessageBox>
#include <QUnhandledException>
#include <limits>
#ifdef QT_DEBUG
    #include <QDebug>
#endif

QByteArray Frame::frameheader = QByteArray("ff");
int Frame::frameLen = 6;
int Frame::frameheaderLen = 1;
int Frame::framehumi = 1;
int Frame::framehumiLen = 2;
int Frame::frametemp = 3;
int Frame::frametempLen = 2;
int Frame::framelight = 5;
int Frame::framelightLen = 1;
QString Frame::framelight_Hvalue = "-1|100";
QString Frame::framelight_MHvalue = "100|140";
QString Frame::framelight_Mvalue = "140|230";
QString Frame::framelight_Lvalue = "230|-1";

QByteArray Frame::sndframeheader = QByteArray("ff");
QByteArray Frame::sndframecheck = QByteArray("01");
QByteArray Frame::sndframeuncheck = QByteArray("00");
QByteArray Frame::sndframebody_0 = QByteArray("00");
QByteArray Frame::sndframebody_1 = QByteArray("0a");
QByteArray Frame::sndframebody_2 = QByteArray("14");
QByteArray Frame::sndframebody_3 = QByteArray("1e");
QByteArray Frame::sndframebody_4 = QByteArray("28");

QPair<int,int> Frame::h_lightSection = qMakePair(0,0);
QPair<int,int> Frame::mh_lightSection = qMakePair(0,0);
QPair<int,int> Frame::m_lightSection = qMakePair(0,0);
QPair<int,int> Frame::l_lightSection = qMakePair(0,0);

Frame::Frame(const QByteArray &data, QObject *parent) :
    dataframe(data),
    QObject(parent),
    ok(false) {
    if(dataframe.left(frameheaderLen).toHex() != frameheader ||
            dataframe.length() != frameLen)
        return;
    ok = true;
}

const QByteArray Frame::getTemperature() {
    return dataframe.mid(frametemp, frametempLen).toHex();
}

const QByteArray Frame::getHumidity() {
    return dataframe.mid(framehumi, framehumiLen).toHex();
}

const QByteArray Frame::getLight() {
    return dataframe.mid(framelight, framelightLen).toHex();
}

bool Frame::parseLightSection() {
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

Frame::LightLevel Frame::parseLightLevel(const int lg) {
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

Frame::LightLevel Frame::getLightLevel() {
    return parseLightLevel(getLight().toInt(nullptr, 16));
}

QByteArray Frame::getControlFrame(bool checked, const int level) {
    QByteArray controlFrame = sndframeheader;
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
    return controlFrame;
}

void Frame::initFrame(const QString &filename) {
    QSettings frame_setting(filename, QSettings::IniFormat);
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
#ifdef QT_DEBUG
    qDebug() << "frameLen:" << frameLen;
    qDebug() << "frameheader:" << frameheader;
    qDebug() << "frameheaderLen:" << frameheaderLen;
    qDebug() << "framehumi:" << framehumi;
    qDebug() << "framehumiLen:" << framehumiLen;
    qDebug() << "framelight:" << framelight;
    qDebug() << "framelightLen:" << framelightLen;
    qDebug() << "frameHValue:" << framelight_Hvalue;
#endif
    if(!parseLightSection()) {
        QMessageBox::critical(NULL, QObject::tr("error"),
                              QObject::tr("paese frame failed"), QMessageBox::Yes);
        throw new QUnhandledException;
    }

    //控制帧配置初始化
    sndframeheader = frame_setting.value("ControlFrame/FrameHeader", "ff").toByteArray();
    sndframecheck = frame_setting.value("ControlFrame/FrameCheck", "01").toByteArray();
    sndframeuncheck = frame_setting.value("ControlFrame/FrameUnCheck", "00").toByteArray();
    sndframebody_0 = frame_setting.value("ControlFrame/FrameBody_0", "00").toByteArray();
    sndframebody_1 = frame_setting.value("ControlFrame/FrameBody_1", "0a").toByteArray();
    sndframebody_2 = frame_setting.value("ControlFrame/FrameBody_2", "14").toByteArray();
    sndframebody_3 = frame_setting.value("ControlFrame/FrameBody_3", "1e").toByteArray();
    sndframebody_4 = frame_setting.value("ControlFrame/FrameBody_4", "28").toByteArray();

#ifdef QT_DEBUG
    qDebug() << "CFrameHeader:" << sndframeheader;
    qDebug() << "CFrameCheck:" << sndframecheck;
    qDebug() << "CFrameUnCheck:" << sndframeuncheck;
    qDebug() << "CFrameBody_0:" << sndframebody_0;
    qDebug() << "CFrameBody_1:" << sndframebody_1;
    qDebug() << "CFrameBody_2:" << sndframebody_2;
    qDebug() << "CFrameBody_3:" << sndframebody_3;
    qDebug() << "CFrameBody_4:" << sndframebody_4;
#endif
}

void Frame::saveFrame(const QString &filename) {
#ifdef QT_DEBUG
    qDebug() << "frameLen:" << frameLen;
    qDebug() << "frameheader:" << frameheader;
    qDebug() << "frameheaderLen:" << frameheaderLen;
    qDebug() << "framehumi:" << framehumi;
    qDebug() << "framehumiLen:" << framehumiLen;
    qDebug() << "framelight:" << framelight;
    qDebug() << "framelightLen:" << framelightLen;
    qDebug() << "frameHValue:" << framelight_Hvalue;
    qDebug() << "cframeheader:" << sndframeheader;
#endif
    QSettings frame_setting(filename, QSettings::IniFormat);
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
