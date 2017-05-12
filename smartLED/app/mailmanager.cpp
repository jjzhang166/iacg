#include "mailmanager.h"
#include <QDebug>

MailManager::MailManager(QObject *parent) : QObject(parent)
    ,ini_setting("cfg.ini", QSettings::IniFormat)
    ,alert_tmp(-1)
    ,alert_humi(-1)
    ,alert_light(-1) {
    USER = ini_setting.value("Mail/User", "").toString();
    PASSWORD = ini_setting.value("Mail/Password", "").toString();
    SENDADDR = ini_setting.value("Mail/SendAddr", "").toString();
    RECVADDR = ini_setting.value("Mail/RecvAddr", "").toString();
    SERVADDR = ini_setting.value("Mail/ServAddr", "").toString();
    PORT = ini_setting.value("Mail/Port", "").toString();
}

MailManager::~MailManager() {
#ifdef QT_DEBUG
    qDebug() << "destroy mail manager";
#endif
    if(!USER.isEmpty()) ini_setting.setValue("Mail/User", USER);
    if(!PASSWORD.isEmpty()) ini_setting.setValue("Mail/Password", PASSWORD);
    if(!SENDADDR.isEmpty()) ini_setting.setValue("Mail/SendAddr", SENDADDR);
    if(!RECVADDR.isEmpty()) ini_setting.setValue("Mail/RecvAddr", RECVADDR);
    if(!SERVADDR.isEmpty()) ini_setting.setValue("Mail/ServAddr", SERVADDR);
    if(!PORT.isEmpty()) ini_setting.setValue("Mail/Port", PORT);
}

void MailManager::setMailData(MAIL_DATA type, QString data) {
    m_data.insert(type, data);
}

QString MailManager::getMailData(MAIL_DATA type) {
    return m_data.value(type);
}

int MailManager::tmpAlert() const {
    return this->alert_tmp;
}

int MailManager::humiAlert() const {
    return this->alert_humi;
}

void MailManager::setTmpAlert(const int &ta) {
    this->alert_tmp = ta;
}

void MailManager::setHumiAlert(const int &ha) {
    this->alert_humi = ha;
}

int MailManager::sendMail(MAIL_TYPE t) {
    MimeMessage msg;
    msg.setSender(new EmailAddress(SENDADDR,QString("smartLED")));
    msg.addRecipient(new EmailAddress(RECVADDR,QString("anonymous")));
    MimeText *content = nullptr;
    switch (t) {
    case MAIL_TMP:
        msg.setSubject(TMPTITLE);
        content = new MimeText(TMPCONTENT);
        break;
    case MAIL_HUMI:
        msg.setSubject(HUMITITLE);
        content = new MimeText(HUMICONTENT);
        break;
    default:
        break;
    }

    msg.addPart(content);
    try {
        if(smtp == nullptr) {
#ifdef QT_DEBUG
            qDebug() << "null pointer";
#endif
            emit(ERR_UNEXCEPT);
            return ERR_UNEXCEPT;
        }
        if(!smtp->sendMail(msg)) {
#ifdef QT_DEBUG
            qDebug() << "send mail error";
#endif
            handleSMTPError(ERR_SENDMAIL_FAILED,content);
            return ERR_SENDMAIL_FAILED;
        }
    }
    catch(...) {
        handleSMTPError(ERR_UNEXCEPT,content);
        return ERR_UNEXCEPT;
    }
    return ERR_SUCCESS;
}

bool MailManager::trytoCreateSmtpInstance() {
    if(USER.isEmpty() || PASSWORD.isEmpty() ||
            SENDADDR.isEmpty() || RECVADDR.isEmpty() ||
            SERVADDR.isEmpty() || PORT.isEmpty())
        return false;
    int res = collMailDataEnd();
    return (res == ERR_SUCCESS)? true : false;
}

int MailManager::collMailDataEnd() {
    if(SERVADDR.isEmpty()) {
        emit collMailEnd(ERR_SERVADDR_EMPTY);
        return ERR_SERVADDR_EMPTY;
    }
    if(PORT.toInt() <= 0) {
        emit collMailEnd(ERR_PORT_EMPTY);
        return ERR_PORT_EMPTY;
    }
    if(USER.isEmpty()) {
        emit collMailEnd(ERR_USER_EMPTY);
        return ERR_USER_EMPTY;
    }
    if(PASSWORD.isEmpty()) {
        emit collMailEnd(ERR_PASSWORD_EMPTY);
        return ERR_PASSWORD_EMPTY;
    }
    if(smtp != nullptr) {
        //delete the old SMTPClient instance
        smtp->quit();
        delete smtp;
        smtp = nullptr;
        //create a new SMTPClient instance
        try {
            smtp = new SmtpClient(SERVADDR,25,SmtpClient::SslConnection);
            smtp->setPort(PORT.toInt());
            smtp->setUser(USER);
            smtp->setPassword(PASSWORD);
            if(!smtp->connectToHost()) {
#ifdef QT_DEBUG
                qDebug() << "connect host error";
#endif
                handleSMTPError(ERR_CONNECT_FAILED,nullptr);
                return ERR_CONNECT_FAILED;
            }
            if(!smtp->login()) {
#ifdef QT_DEBUG
                qDebug() << "login error";
#endif
                handleSMTPError(ERR_LOGIN_FAILED,nullptr);
                return ERR_LOGIN_FAILED;
            }
        }
        catch(...) {
            handleSMTPError(ERR_UNEXCEPT,nullptr);
            return ERR_UNEXCEPT;
        }
        emit collMailEnd(ERR_CLIENT_EXIST);
        return ERR_CLIENT_EXIST;
    }
    //if smtp == null,we create a new instance directly
    try {
        smtp = new SmtpClient(SERVADDR,25,SmtpClient::SslConnection);
        smtp->setPort(PORT.toInt());
        smtp->setUser(USER);
        smtp->setPassword(PASSWORD);
        if(!smtp->connectToHost()) {
#ifdef QT_DEBUG
            qDebug() << "connect host error";
#endif
            handleSMTPError(ERR_CONNECT_FAILED,nullptr);
            return ERR_CONNECT_FAILED;
        }
        if(!smtp->login()) {
#ifdef QT_DEBUG
            qDebug() << "login error";
#endif
            handleSMTPError(ERR_LOGIN_FAILED,nullptr);
            return ERR_LOGIN_FAILED;
        }
    }
    catch(...) {
        handleSMTPError(ERR_UNEXCEPT,nullptr);
        return ERR_UNEXCEPT;
    }

    emit collMailEnd(ERR_SUCCESS);
    return ERR_SUCCESS;
}

void MailManager::handleSMTPError(MAIL_ERROR err,MimeText *ct) {
    smtp->quit();
    delete smtp;
    if(ct != nullptr) {
        delete ct;
        ct = nullptr;
    }
    smtp = nullptr;
    emit collMailEnd(err);
}

int MailManager::collTempDataEnd() {
    if(TMPTITLE.isEmpty()) {
        emit collTempEnd(ERR_TITLE_EMPTY);
        return ERR_TITLE_EMPTY;
    }
    if(TMPCONTENT.isEmpty()) {
        emit collTempEnd(ERR_CONTENT_EMPTY);
        return ERR_CONTENT_EMPTY;
    }
    emit collTempEnd(ERR_SUCCESS);
    return ERR_SUCCESS;
}

int MailManager::collHumiDataEnd() {
    if(HUMITITLE.isEmpty()) {
        emit collHumiEnd(ERR_TITLE_EMPTY);
        return ERR_TITLE_EMPTY;
    }
    if(HUMICONTENT.isEmpty()) {
        emit collHumiEnd(ERR_CONTENT_EMPTY);
        return ERR_CONTENT_EMPTY;
    }
    emit collHumiEnd(ERR_SUCCESS);
    return ERR_SUCCESS;
}

void MailManager::collDataStart() {
    emit collData();
}

uint MailManager::getCurTimeSec() {
    QDateTime time = QDateTime::currentDateTime();
    return time.toTime_t();
}
