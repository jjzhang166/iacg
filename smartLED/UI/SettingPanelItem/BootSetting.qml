import QtQuick 2.0
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 100
        title: qsTr("BootSetting")
        fontfamily: fontmanager.curfont
        content: Rectangle{
            SLCheckBox {
                id: checkbox_smtp
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 200
                fontfamily: fontmanager.curfont
                text: qsTr("SmtpBoot")
                checked: bootmanager.smtpBoot
                onCheckedChanged: bootmanager.smtpBoot = checked
            }

            SLCheckBox {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: checkbox_smtp.right
                anchors.leftMargin: 30
                fontfamily: fontmanager.curfont
                text: qsTr("SerialportBoot")
                checked: bootmanager.serialportBoot
                onCheckedChanged: bootmanager.serialportBoot = checked
            }

            SLCheckBox {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: checkbox_smtp.left
                anchors.rightMargin: 30
                fontfamily: fontmanager.curfont
                text: qsTr("WindowShadow")
                checked: bootmanager.winShadow
                onCheckedChanged: bootmanager.winShadow = checked
            }
        }
    }
}
