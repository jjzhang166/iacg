#include "mailmanager.h"
#include <QDebug>

MailManager::MailManager(DataManager *dm,QObject *parent) : QObject(parent)
    ,datamanager(dm)
    ,alert_tmp(-1)
    ,alert_humi(-1)
    ,alert_light(-1) {
    m_user = dm->ReadMailData(DataManager::MAIL_USER).toString();
    m_passwd = dm->ReadMailData(DataManager::MAIL_PASSWORD).toString();
    m_sndaddr = dm->ReadMailData(DataManager::MAIL_SENDADDR).toString();
    m_recvaddr = dm->ReadMailData(DataManager::MAIL_RECVADDR).toString();
    m_servaddr = dm->ReadMailData(DataManager::MAIL_SERVERADDR).toString();
    m_port = dm->ReadMailData(DataManager::MAIL_PORT).toString();
}

MailManager::~MailManager() {
    datamanager->WriteMailData(DataManager::MAIL_USER, m_user);
    datamanager->WriteMailData(DataManager::MAIL_PASSWORD, m_passwd);
    datamanager->WriteMailData(DataManager::MAIL_SENDADDR, m_sndaddr);
    datamanager->WriteMailData(DataManager::MAIL_RECVADDR, m_recvaddr);
    datamanager->WriteMailData(DataManager::MAIL_SERVERADDR, m_servaddr);
    datamanager->WriteMailData(DataManager::MAIL_PORT, m_port);
}

int MailManager::tmpAlert() const {
    return this->alert_tmp;
}

int MailManager::humiAlert() const {
    return this->alert_humi;
}

int MailManager::lightAlert() const {
    return this->alert_light;
}

QString MailManager::user() const {
    return this->m_user;
}

QString MailManager::passwd() const {
    return this->m_passwd;
}

QString MailManager::sndaddr() const {
    return this->m_sndaddr;
}

QString MailManager::recvaddr() const {
    return this->m_recvaddr;
}

QString MailManager::tmp_title() const {
    return this->m_tmptitle;
}

QString MailManager::tmp_content() const {
    return this->m_tmpcontent;
}

QString MailManager::humi_title() const {
    return this->m_humititle;
}

QString MailManager::humi_content() const {
    return this->m_humicontent;
}

QString MailManager::light_title() const {
    return this->m_lighttitle;
}

QString MailManager::light_content() const {
    return this->m_lightcontent;
}

QString MailManager::servaddr() const {
    return this->m_servaddr;
}

QString MailManager::port() const {
    return this->m_port;
}

void MailManager::setTmpAlert(const int &ta) {
    this->alert_tmp = ta;
}

void MailManager::setHumiAlert(const int &ha) {
    this->alert_humi = ha;
}

void MailManager::setLightAlert(const int &la) {
    this->alert_light = la;
}

void MailManager::setUser(const QString &usr) {
    this->m_user = usr;
}

void MailManager::setPasswd(const QString &pwd) {
    this->m_passwd = pwd;
}

void MailManager::setSndaddr(const QString &saddr) {
    this->m_sndaddr = saddr;
}

void MailManager::setRecvaddr(const QString &raddr) {
    this->m_recvaddr = raddr;
}

void MailManager::setTmp_title(const QString &t) {
    this->m_tmptitle = t;
}

void MailManager::setTmp_content(const QString &ct) {
    this->m_tmpcontent = ct;
}

void MailManager::setHumi_title(const QString &ht) {
    this->m_humititle = ht;
}

void MailManager::setHumi_content(const QString &hc) {
    this->m_humicontent = hc;
}

void MailManager::setLight_title(const QString &lt) {
    this->m_lighttitle = lt;
}

void MailManager::setLight_content(const QString &lc) {
    this->m_lightcontent = lc;
}

void MailManager::setServaddr(const QString &saddr) {
    this->m_servaddr = saddr;
}

void MailManager::setPort(const QString &port) {
    this->m_port = port;
}

int MailManager::sendMail(MAIL_TYPE t) {
    MimeMessage msg;
    msg.setSender(new EmailAddress(m_sndaddr,QString("smartLED")));
    msg.addRecipient(new EmailAddress(m_recvaddr,QString("anonymous")));
    MimeText *content = nullptr;
    switch (t) {
    case MAIL_TMP:
        msg.setSubject(this->m_tmptitle);
        content = new MimeText(this->m_tmpcontent);
        break;
    case MAIL_HUMI:
        msg.setSubject(this->m_humititle);
        content = new MimeText(this->m_humicontent);
        break;
/*
    case MAIL_LIGHT:
        msg.setSubject(this->m_lighttitle);
        content = new MimeText(this->m_lightcontent);
        break;
*/
    default:
        break;
    }

    msg.addPart(content);
    try {
        if(smtp == nullptr) {
            qDebug() << "null pointer";
            emit(ERR_UNEXCEPT);
            return ERR_UNEXCEPT;
        }
        if(!smtp->sendMail(msg)) {
            qDebug() << "send mail error";
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
    if(m_user.isEmpty() || m_passwd.isEmpty() ||
            m_sndaddr.isEmpty() || m_recvaddr.isEmpty() ||
            m_servaddr.isEmpty() || m_port.isEmpty())
        return false;
    int res = collMailDataEnd();
    return (res == ERR_SUCCESS)? true : false;
}

int MailManager::collMailDataEnd() {
    if(m_servaddr.isEmpty()) {
        emit collMailEnd(ERR_SERVADDR_EMPTY);
        return ERR_SERVADDR_EMPTY;
    }
    if(m_port.toInt() <= 0) {
        emit collMailEnd(ERR_PORT_EMPTY);
        return ERR_PORT_EMPTY;
    }
    if(m_user.isEmpty()) {
        emit collMailEnd(ERR_USER_EMPTY);
        return ERR_USER_EMPTY;
    }
    if(m_passwd.isEmpty()) {
        emit collMailEnd(ERR_PASSWORD_EMPTY);
        return ERR_PASSWORD_EMPTY;
    }
    if(smtp != nullptr) {
        //delete the old SMTPClient instance
        smtp->quit();
        delete smtp;
        smtp = nullptr;
        //create a new SMTPClient instance
        try{
            smtp = new SmtpClient(m_servaddr,25,SmtpClient::SslConnection);
            smtp->setPort(m_port.toInt());
            smtp->setUser(m_user);
            smtp->setPassword(m_passwd);
            if(!smtp->connectToHost()) {
                qDebug() << "connect host error";
                handleSMTPError(ERR_CONNECT_FAILED,nullptr);
                return ERR_CONNECT_FAILED;
            }
            if(!smtp->login()) {
                qDebug() << "login error";
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
        smtp = new SmtpClient(m_servaddr,25,SmtpClient::SslConnection);
        smtp->setPort(m_port.toInt());
        smtp->setUser(m_user);
        smtp->setPassword(m_passwd);
        if(!smtp->connectToHost()) {
            qDebug() << "connect host error";
            handleSMTPError(ERR_CONNECT_FAILED,nullptr);
            return ERR_CONNECT_FAILED;
        }
        if(!smtp->login()) {
            qDebug() << "login error";
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
    if(m_tmptitle.isEmpty()) {
        emit collTempEnd(ERR_TITLE_EMPTY);
        return ERR_TITLE_EMPTY;
    }
    if(m_tmpcontent.isEmpty()) {
        emit collTempEnd(ERR_CONTENT_EMPTY);
        return ERR_CONTENT_EMPTY;
    }
    emit collTempEnd(ERR_SUCCESS);
    return ERR_SUCCESS;
}

int MailManager::collHumiDataEnd() {
    if(m_humititle.isEmpty()) {
        emit collHumiEnd(ERR_TITLE_EMPTY);
        return ERR_TITLE_EMPTY;
    }
    if(m_humicontent.isEmpty()) {
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
