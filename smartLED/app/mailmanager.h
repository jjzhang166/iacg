#ifndef MAILDATA_H
#define MAILDATA_H
#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QSettings>

#include "smtpClient/SmtpMime"

class MailManager : public QObject {
    Q_OBJECT
    Q_ENUMS(MAIL_TYPE)
    Q_ENUMS(MAIL_ERROR)
    Q_ENUMS(MAIL_DATA)

    Q_PROPERTY(int tmpAlert READ tmpAlert WRITE setTmpAlert)
    Q_PROPERTY(int humiAlert READ humiAlert WRITE setHumiAlert)

signals:
    void collData();
    void collMailEnd(const int &res);
    void collTempEnd(const int &res);
    void collHumiEnd(const int &res);

public:
    enum MAIL_DATA {
        DATA_USER,
        DATA_PASSWORD,
        DATA_SENDADDR,
        DATA_RECVADDR,
        DATA_TMPTITLE,
        DATA_TMPCONTENT,
        DATA_HUMITITLE,
        DATA_HUMICONTENT,
        DATA_LIGHTTITLE,
        DATA_LIGHTCONTENT,
        DATA_SERVADDR,
        DATA_PORT
    };

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

    MailManager(QObject *parent = 0);
    ~MailManager();

public:

    int tmpAlert() const;
    void setTmpAlert(const int &ta);

    int humiAlert() const;
    void setHumiAlert(const int &ha);

    Q_INVOKABLE void setMailData(MAIL_DATA type, QString data);
    Q_INVOKABLE QString getMailData(MAIL_DATA type);

    Q_INVOKABLE int sendMail(MAIL_TYPE t);
    Q_INVOKABLE void collDataStart();
    Q_INVOKABLE int collMailDataEnd();
    Q_INVOKABLE int collTempDataEnd();
    Q_INVOKABLE int collHumiDataEnd();
    Q_INVOKABLE uint getCurTimeSec();

    bool trytoCreateSmtpInstance();

private:
    #define USER            m_data[0]
    #define PASSWORD        m_data[1]
    #define SENDADDR        m_data[2]
    #define RECVADDR        m_data[3]
    #define TMPTITLE        m_data[4]
    #define TMPCONTENT      m_data[5]
    #define HUMITITLE       m_data[6]
    #define HUMICONTENT     m_data[7]
    #define LIGHTTITLE      m_data[8]
    #define LIGHTCONTENT    m_data[9]
    #define SERVADDR        m_data[10]
    #define PORT            m_data[11]

private:
    QSettings ini_setting;

    enum _timeout{
        TIME_OUT_LOW = 2000,
        TIME_OUT_MIDDLE = 5000,
        TIME_OUT_HIGH = 10000
    };

    SmtpClient *smtp = nullptr;

    int alert_tmp;
    int alert_humi;
    int alert_light;
    QMap<int, QString> m_data;

private:
    void handleSMTPError(MAIL_ERROR err,MimeText *ct);
};

#endif // MAILDATA_H
