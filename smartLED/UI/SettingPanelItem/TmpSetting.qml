import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0
import Manager.Mail 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 280
        title: qsTr("TmpSetting")
        fontfamily: fontmanager.curfont
        content: Rectangle {

            Connections {
                target: maildata
                onCollMailEnd: {
                    if(res == 1 || res == -9) {
                        console.log("coll mail end,and coll temp start")
                        if(!check1.checked) {
                            maildata.tmpAlert = -1
                            return
                        }
                        else
                            maildata.tmpAlert = parseInt(input_alertvalue.text)
                        maildata.setMailData(MailManager.DATA_TMPTITLE, input_title.text)
                        maildata.setMailData(MailManager.DATA_TMPCONTENT, input_content.text)
                        if(maildata.collTempDataEnd() === 1)
                            return
                        check1.checked = false
                        maildata.tmpAlert = -1
                        return
                    }
                    check1.checked =false
                    maildata.tmpAlert = -1
                }
            }

            SLCheckBox {
                id: check1
                text: qsTr("AutoSendMail")
                fontfamily: fontmanager.curfont
                checked: false
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 40
            }
            Text {
                id: t1
                text: qsTr("AlertValue:")
                anchors.left: check1.right
                anchors.leftMargin: 40
                anchors.verticalCenter: check1.verticalCenter
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_alertvalue
                anchors.left: t1.right
                anchors.leftMargin: 10
                anchors.verticalCenter: t1.verticalCenter
                width: 30
                inputMask: "99"
                font.family: fontmanager.curfont
                tooltip_fontfamily: fontmanager.curfont
            }
            SLTextInput {
                id: input_title
                anchors.top: check1.bottom
                anchors.topMargin: 18
                anchors.left: parent.left
                anchors.leftMargin: 60
                width: 220
                tooltip: qsTr("No Title")
                tooltip_fontfamily: fontmanager.curfont
                font.family: fontmanager.curfont
            }
            SLTextInput {
                id: input_content
                anchors.top: input_title.bottom
                anchors.topMargin: 13
                anchors.left: parent.left
                anchors.leftMargin: 40
                width: 270
                height: 142
                tooltip: qsTr("Test Message")
                tooltip_fontfamily: fontmanager.curfont
                font.family: fontmanager.curfont
            }
        }
    }
}
