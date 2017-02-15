import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 235
        title: qsTr("MailSetting")
        content: Rectangle {
            Connections {
                target: maildata
                onCollData: {
                    maildata.servaddr = input_server.text
                    maildata.port = input_port.text
                    maildata.user = input_user.text
                    maildata.passwd = input_psw.text
                    maildata.sndaddr = input_snd.text
                    maildata.recvaddr = input_recv.text
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
            }
            SLTextInput {
                id: input_server
                width: 200
                anchors.verticalCenter: t1.verticalCenter
                anchors.verticalCenterOffset: 2
                anchors.left: parent.left
                anchors.leftMargin: 120
                tooltip: qsTr("smtp server address")
            }
            Text {
                id: t2
                anchors.left: input_server.right
                anchors.leftMargin: 40
                anchors.verticalCenter: t1.verticalCenter
                text: qsTr("Port:")
            }
            SLTextInput {
                id: input_port
                anchors.left: t2.right
                anchors.leftMargin: 13
                anchors.verticalCenter: t2.verticalCenter
                anchors.verticalCenterOffset: 2
                tooltip: qsTr("smtp port")
            }
            Text {
                id: t3
                anchors.top: t1.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("User:")
            }
            SLTextInput {
                id: input_user
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t3.verticalCenter
                anchors.verticalCenterOffset: 2
                tooltip: qsTr("user name")
                width: 240
            }
            Text {
                id: t4
                anchors.top: t3.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("Password:")
            }
            SLTextInput {
                id: input_psw
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t4.verticalCenter
                anchors.verticalCenterOffset: 2
                tooltip: qsTr("password")
                width: 240
            }
            Text {
                id: t5
                anchors.top: t4.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("SendBox:")
            }
            SLTextInput {
                id: input_snd
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t5.verticalCenter
                anchors.verticalCenterOffset: 2
                tooltip: qsTr("sending mailbox's address")
                width: 240
            }
            Text {
                id: t6
                anchors.top: t5.bottom
                anchors.topMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: qsTr("RecvBox:")
            }
            SLTextInput {
                id: input_recv
                anchors.left: parent.left
                anchors.leftMargin: 120
                anchors.verticalCenter: t6.verticalCenter
                anchors.verticalCenterOffset: 2
                tooltip: qsTr("recv mailbox's address")
                width: 240
            }
        }
    }
}
