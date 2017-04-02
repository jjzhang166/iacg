import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 70

    SLMsgDialog {
        id: dia
        dia_title: qsTr("error")
        dia_icon_type: 1
        dia_text_leftmargin: 30
        dia_width: 280
    }

    Connections {
        target: maildata
        onCollMailEnd: {
            switch(res) {
            case -5:        //ERR_SERVADDR_EMPTY
                dia.dia_content = qsTr("server addr is empty")
                break
            case -6:        //ERR_PORT_EMPTY
                dia.dia_content = qsTr("port is empty")
                break
            case -7:        //ERR_USER_EMPTY
                dia.dia_content = qsTr("user is empty")
                break
            case -8:        //ERR_PASSWORD_EMPTY
                dia.dia_content = qsTr("password is empty")
                break
            case -9:        //ERR_CLIENT_EXIST
                dia.dia_icon_type = 0
                dia.dia_width = 320
                dia.dia_title = qsTr("info")
                dia.dia_content = qsTr("client is already exist,reset all data")
                break
            case -1:        //ERR_CONNECT_FAILED
                dia.dia_content = qsTr("connect error")
                break
            case -2:        //ERR_LOGIN_FAILED
                dia.dia_content = qsTr("login error")
                break
            case -3:       //ERR_SENDMAIL_FAILED
                dia.dia_content = qsTr("send mail error")
                break
            /*case -4:        //ERR_BUSY
                dia.dia_icon_type = 0
                dia.dia_content = qsTr("program is busy")
                break*/
            case 1:         //ERR_SUCCESS
                dia.dia_icon_type = 0
                dia.dia_title = qsTr("success")
                dia.dia_content = qsTr("set data ok")
                break
            default:
                dia.dia_content = qsTr("unexcepted error")
                break
            }
            dia.dia_icon_type = 1
            dia.open()
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 525
        height: 60
        SLFlatButton {
            id: btn_save
            anchors.right: parent.right
            anchors.rightMargin: 80
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("SaveSettings")
            fontfamily: fontmanager.curfont
            width: 150
            onClicked:
                maildata.collDataStart()
        }
    }
}
