﻿#include "mailmanager.h"
#include <QDebug>

MailManager::MailManager(DataManager *dm,QObject *parent) : QObject(parent)
    ,datamanager(dm)
    ,alert_tmp(-1)
    ,alert_humi(-1)
    ,alert_light(-1) {
    USER = dm->ReadMailData(DataManager::MAIL_USER).toString();
    PASSWORD = dm->ReadMailData(DataManager::MAIL_PASSWORD).toString();
    SENDADDR = dm->ReadMailData(DataManager::MAIL_SENDADDR).toString();
    RECVADDR = dm->ReadMailData(DataManager::MAIL_RECVADDR).toString();
    SERVADDR = dm->ReadMailData(DataManager::MAIL_SERVERADDR).toString();
    PORT = dm->ReadMailData(DataManager::MAIL_PORT).toString();
}

MailManager::~MailManager() {
    qDebug() << "destroy mail manager";
    datamanager->WriteMailData(DataManager::MAIL_USER, USER);
    datamanager->WriteMailData(DataManager::MAIL_PASSWORD, PASSWORD);
    datamanager->WriteMailData(DataManager::MAIL_SENDADDR, SENDADDR);
    datamanager->WriteMailData(DataManager::MAIL_RECVADDR, RECVADDR);
    datamanager->WriteMailData(DataManager::MAIL_SERVERADDR, SERVADDR);
    datamanager->WriteMailData(DataManager::MAIL_PORT, PORT);
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
        smtp = new SmtpClient(SERVADDR,25,SmtpClient::SslConnection);
        smtp->setPort(PORT.toInt());
        smtp->setUser(USER);
        smtp->setPassword(PASSWORD);
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
