#ifndef FRAME_H
#define FRAME_H

#include <QByteArray>
#include <QString>
#include <QPair>
#include <QSettings>
#include <QObject>

class Frame : public QObject {
public:
    enum LightLevel {
        LL_HIGH,
        LL_MH,
        LL_MEDIUM,
        LL_LOW,
        LL_ERROR = -1
    };

public:
    Frame(const QByteArray &data, QObject *parent = nullptr);

public:
    static void initFrame(const QString &filename = "frame.ini");
    static void saveFrame(const QString &filename = "frame.ini");
    static QByteArray getControlFrame(bool checked, const int level);
    const QByteArray getTemperature();
    const QByteArray getHumidity();
    LightLevel getLightLevel();
    bool ok;

private:
    static bool parseLightSection();
    const QByteArray getLight();
    LightLevel parseLightLevel(const int lg);

private:
    static QByteArray frameheader;
    static int frameLen;
    static int frameheaderLen;
    static int framehumi;
    static int framehumiLen;
    static int frametemp;
    static int frametempLen;
    static int framelight;
    static int framelightLen;
    static QString framelight_Hvalue;     //高光照强度区间
    static QString framelight_MHvalue;    //中高光照强度区间
    static QString framelight_Mvalue;     //中等光照强度区间
    static QString framelight_Lvalue;     //低光照强度区间

    //控制帧相关信息
    static QByteArray sndframeheader;
    static QByteArray sndframecheck;
    static QByteArray sndframeuncheck;
    static QByteArray sndframebody_0;
    static QByteArray sndframebody_1;
    static QByteArray sndframebody_2;
    static QByteArray sndframebody_3;
    static QByteArray sndframebody_4;

private:
    const QByteArray dataframe;
    static QPair<int,int> h_lightSection;
    static QPair<int,int> mh_lightSection;
    static QPair<int,int> m_lightSection;
    static QPair<int,int> l_lightSection;
};

#endif // FRAME_H
