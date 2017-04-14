import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0
import Manager.Mail 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        id: sg
        width: parent.width
        height: 235
        title: qsTr("MailSetting")
        fontfamily: fontmanager.curfont
        content: Rectangle {
            Connections {
                target: maildata
                onCollData: {
                    maildata.setMailData(MailManager.DATA_SERVADDR, input_server.text)
                    maildata.setMailData(MailManager.DATA_PORT, input_port.text)
                    maildata.setMailData(MailManager.DATA_USER, input_user.text)
                    maildata.setMailData(MailManager.DATA_PASSWORD, input_psw.text)
                    maildata.setMailData(MailManager.DATA_SENDADDR, input_snd.text)
                    maildata.setMailData(MailManager.DATA_RECVADDR, input_recv.text)
                    maildata.collMailDataEnd()
                    console.log("coll mail data and create the SMTPClient instance")
                }
            }

            Text {
                id: t1
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("SmtpServer:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_server
                width: 200
                anchors.verticalCenter: t1.verticalCenter
                anchors.verticalCenterOffset: 2
                anchors.left: parent.left
                anchors.leftMargin: 120
                text: maildata.getMailData(MailManager.DATA_SERVADDR)
                tooltip: qsTr("smtp server address")
                tooltip_fontfamily: fontmanager.curfont
                font.family: fontmanager.curfont
            }
            Text {
                id: t2
                anchors.left: input_server.right
                anchors.leftMargin: 40
                anchors.verticalCenter: t1.verticalCenter
                text: qsTr("Port:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_port
                anchors.left: t2.right
                anchors.leftMargin: 13
                anchors.verticalCenter: t2.verticalCenter
                anchors.verticalCenterOffset: 2
                text: maildata.getMailData(MailManager.DATA_PORT)
                tooltip: qsTr("smtp port")
                tooltip_fontfamily: fontmanager.curfont
                font.family: fontmanager.curfont
            }
            Text {
                id: t3
                anchors.top: t1.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("User:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_user
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t3.verticalCenter
                anchors.verticalCenterOffset: 2
                text: maildata.getMailData(MailManager.DATA_USER)
                tooltip: qsTr("user name")
                tooltip_fontfamily: fontmanager.curfont
                width: 240
                font.family: fontmanager.curfont
            }
            Text {
                id: t4
                anchors.top: t3.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("Password:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_psw
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t4.verticalCenter
                anchors.verticalCenterOffset: 2
                text: maildata.getMailData(MailManager.DATA_PASSWORD)
                tooltip: qsTr("password")
                tooltip_fontfamily: fontmanager.curfont
                width: 240
                font.family: fontmanager.curfont
            }
            Text {
                id: t5
                anchors.top: t4.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("SendBox:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_snd
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t5.verticalCenter
                anchors.verticalCenterOffset: 2
                text: maildata.getMailData(MailManager.DATA_SENDADDR)
                tooltip: qsTr("sending mailbox's address")
                tooltip_fontfamily: fontmanager.curfont
                width: 240
                font.family: fontmanager.curfont
            }
            Text {
                id: t6
                anchors.top: t5.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("RecvBox:")
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_recv
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t6.verticalCenter
                anchors.verticalCenterOffset: 2
                text: maildata.getMailData(MailManager.DATA_RECVADDR)
                tooltip: qsTr("recv mailbox's address")
                tooltip_fontfamily: fontmanager.curfont
                width: 240
                font.family: fontmanager.curfont
            }
        }
    }
}
