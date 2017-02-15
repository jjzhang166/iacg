/*
 *当光照小于某值时，自动给指定邮箱发送邮件
 *注：传感器搜集的光照数据精度太低，弃用本功能
 */
import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 280
        title: qsTr("LightSetting")
        content: Rectangle {
            Connections {
                target: maildata
                onCollData: {
                    if(!check1.checked)
                        maildata.lightAlert = -1
                    else
                        maildata.lightAlert = input_alertvalue.currentText == "Low"? 100:
                                input_alertvalue.currentText == "Middle"? 140:230
                    maildata.light_title = input_title.text
                    maildata.light_content = input_content.text
                    console.log("light value:"+maildata.lightAlert)
                    console.log("light title:"+maildata.light_title)
                    console.log("light content:"+maildata.light_content)
                }
            }
            SLCheckBox {
                id: check1
                text: qsTr("AutoSendMail")
                checked: false
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 40
            }
            Text {
                id: t1
                text: qsTr("AlertLevel:")
                anchors.left: check1.right
                anchors.leftMargin: 40
                anchors.verticalCenter: check1.verticalCenter
            }
            SLComboBox {
                id: input_alertvalue
                anchors.left: t1.right
                anchors.leftMargin: 10
                anchors.verticalCenter: t1.verticalCenter
                height: 18
                width: 95
                model: ["Low","Middle","High"]
            }
            SLTextInput {
                id: input_title
                anchors.top: check1.bottom
                anchors.topMargin: 18
                anchors.left: parent.left
                anchors.leftMargin: 60
                width: 220
                tooltip: qsTr("No Title")
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
            }
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 280
        width: 525
        height: 60
        SLFlatButton {
            id: btn_save
            anchors.right: parent.right
            anchors.rightMargin: 80
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("SaveSettings")
            width: 150
            onClicked:
                maildata.collDataStart()
        }
    }
}
