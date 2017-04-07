#ifndef MAILDATA_H
#define MAILDATA_H
#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>

#include "smtpClient/SmtpMime"
#include "datamanager.h"

class MailManager : public QObject {
    Q_OBJECT
    Q_ENUMS(MAIL_TYPE)
    Q_ENUMS(MAIL_ERROR)

    /*以下为MailData类的属性表:
     *user: 保存登陆邮箱的用户名
     *passwd: 保存登陆邮箱的密码
     *sndaddr: 保存发件箱的地址
     *recvaddr: 保存收件箱的地址
     *tmp_title: 温度邮件的标头
     *tmp_content: 温度邮件的内容
     *humi_title,humi_content同上
     *light_title,light_content弃用
     *servaddr: SMTP服务器的地址
     *port: SMTP服务器的端口
     *tmpAlert: 发送温度邮件的阈值，当设为-1时不发送，当超过
     * 此值的时候发送温度邮件
     * humiAlert作用同上，lightAlert弃用
     */
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString passwd READ passwd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(QString sndaddr READ sndaddr WRITE setSndaddr NOTIFY sndaddrChanged)
    Q_PROPERTY(QString recvaddr READ recvaddr WRITE setRecvaddr NOTIFY recvaddrChanged)
    Q_PROPERTY(QString tmp_title READ tmp_title WRITE setTmp_title)
    Q_PROPERTY(QString tmp_content READ tmp_content WRITE setTmp_content)
    Q_PROPERTY(QString humi_title READ humi_title WRITE setHumi_title)
    Q_PROPERTY(QString humi_content READ humi_content WRITE setHumi_content)
    Q_PROPERTY(QString light_title READ light_title WRITE setLight_title)
    Q_PROPERTY(QString light_content READ light_content WRITE setLight_content)
    Q_PROPERTY(QString servaddr READ servaddr WRITE setServaddr NOTIFY servaddrChanged)
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(int tmpAlert READ tmpAlert WRITE setTmpAlert)
    Q_PROPERTY(int humiAlert READ humiAlert WRITE setHumiAlert)
    Q_PROPERTY(int lightAlert READ lightAlert WRITE setLightAlert)
    Q_ENUMS(MAIL_TYPE)

    /*
     *以下为类信号描述：
     * collData(): 当搜集邮箱、温度、光照时发送此信号
     * collMailEnd(const int &res): 当搜集邮箱信息结束时发送此信号
     * collTempEnd(const int &res): 当搜集温度信息结束时发送此信号
     * collHumiEnd(const int &res): 当搜集湿度信息结束时发送此信号
     * 参数res(enum MAIL_ERROR): 指示搜集数据是否成功，如果不成功则指示发生了何种错误
     */
signals:
    void collData();
    void collMailEnd(const int &res);
    void collTempEnd(const int &res);
    void collHumiEnd(const int &res);

    void userChanged(const QString &user);
    void passwdChanged(const QString &passwd);
    void sndaddrChanged(const QString &sndaddr);
    void recvaddrChanged(const QString &recvaddr);
    void servaddrChanged(const QString &servaddr);
    void portChanged(const QString &port);

public:
    //当前发送的邮件类型
    enum MAIL_TYPE {
        MAIL_TMP = 0,
        MAIL_HUMI = 1,
        MAIL_LIGHT = 2
    };
    //发送邮件可能产生的错误
    enum MAIL_ERROR {
        ERR_SUCCESS = 1,                //发送成功
        ERR_CONNECT_FAILED = -1,        //连接服务器失败
        ERR_LOGIN_FAILED = -2,          //登陆失败
        ERR_SENDMAIL_FAILED = -3,       //发送邮件失败
        ERR_BUSY = -4,                  //弃用值
        ERR_SERVADDR_EMPTY = -5,        //服务器地址为空
        ERR_PORT_EMPTY = -6,            //服务器端口为空
        ERR_USER_EMPTY = -7,            //用户名为空
        ERR_PASSWORD_EMPTY = -8,        //密码为空
        ERR_CLIENT_EXIST = -9,          //已存在的客户端实例
        ERR_UNEXCEPT = -10,             //无法预知的错误
        ERR_TITLE_EMPTY = -11,          //邮件没有标题
        ERR_CONTENT_EMPTY = -12         //邮件没有内容
    };

    MailManager(DataManager *dm,QObject *parent = 0);
    ~MailManager();

public:
    int tmpAlert() const;
    void setTmpAlert(const int &ta);

    int humiAlert() const;
    void setHumiAlert(const int &ha);

    int lightAlert() const;
    void setLightAlert(const int &la);

    QString user() const;
    void setUser(const QString &usr);

    QString passwd() const;
    void setPasswd(const QString &pwd);

    QString sndaddr() const;
    void setSndaddr(const QString &saddr);

    QString recvaddr() const;
    void setRecvaddr(const QString &raddr);

    QString tmp_title() const;
    void setTmp_title(const QString &t);

    QString tmp_content() const;
    void setTmp_content(const QString &ct);

    QString humi_title() const;
    void setHumi_title(const QString &ht);

    QString humi_content() const;
    void setHumi_content(const QString &hc);

    QString light_title() const;
    void setLight_title(const QString &lt);

    QString light_content() const;
    void setLight_content(const QString &lc);

    QString servaddr() const;
    void setServaddr(const QString &saddr);

    QString port() const;
    void setPort(const QString &port);

    /*
     * 名称: sendMail
     * 参数: MAIL_TYPE,指示当前发送何种类型的邮件
     * 返回值: int,指示发送邮件是否成功
     * 作用: 向已配置好的邮箱发送一封邮件
     */
    Q_INVOKABLE int sendMail(MAIL_TYPE t);
    /*
     * 名称: collDataStart
     * 参数: 无
     * 返回值: 无
     * 作用: 告知QML层,开始数据搜集
     */
    Q_INVOKABLE void collDataStart();
    /*
     * 名称: collMailDataEnd
     * 参数: 无
     * 返回值: int,为MAIL_ERROR中的某个值,指示邮箱数据搜集是否成功
     * 作用: 通过搜集的邮箱信息创建SMTP实例,如无错误，开始温度和湿度
     * 数据信息的搜集
     */
    Q_INVOKABLE int collMailDataEnd();
    /*
     * 名称: collTempDataEnd
     * 参数: 无
     * 返回值: int,为MAIL_ERROR中的某个值,指示温度数据搜集是否成功
     * 作用: 搜集温度邮件的详细内容,如无错误,当满足发送条件时，即按此
     * 内容发送邮件
     */
    Q_INVOKABLE int collTempDataEnd();
    Q_INVOKABLE int collHumiDataEnd();
    /*
     * 名称: getCurTimeSec
     * 参数: 无
     * 返回值: uint
     * 作用: 返回一个当前的时间戳, 用于间歇性发送邮件
     */
    Q_INVOKABLE uint getCurTimeSec();

    bool trytoCreateSmtpInstance();

private:
    DataManager *datamanager;

    enum _timeout{
        TIME_OUT_LOW = 2000,
        TIME_OUT_MIDDLE = 5000,
        TIME_OUT_HIGH = 10000
    };

    QString m_user;
    QString m_passwd;
    QString m_sndaddr;
    QString m_recvaddr;
    QString m_tmptitle;
    QString m_humititle;
    QString m_lighttitle;
    QString m_tmpcontent;
    QString m_humicontent;
    QString m_lightcontent;
    QString m_servaddr;
    QString m_port;

    SmtpClient *smtp = nullptr;

    int alert_tmp;
    int alert_humi;
    int alert_light;

private:
    void handleSMTPError(MAIL_ERROR err,MimeText *ct);
};

#endif // MAILDATA_H
