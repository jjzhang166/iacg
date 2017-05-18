import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import SLComponent 1.0

Dialog {
    id: notify_dia
    title: qsTr("alertSetting")
    modality: Qt.ApplicationModal
    contentItem: Rectangle {
        implicitHeight: 190
        implicitWidth: 270
        SLCheckBox {
            id: checkBox
            enabled: notifymanager.notifyValid
            x: 30
            y: 15
            fontfamily: fontmanager.curfont
            text: qsTr("EnableNotify")
            checked: notifymanager.notifyEnable
            onEnabledChanged:
                checkBox.fontcolor = enabled? "black" : "gray"
        }

        ComboBox {
            id: comboBox
            width: 135
            height: 18
            enabled: checkBox.checked
            anchors.left: text1.right
            anchors.leftMargin: 22
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: text1.verticalCenter
            model: [qsTr("LL_H"), qsTr("LL_MH"), qsTr("LL_MEDIUM"), qsTr("LL_LOW")]
            currentIndex: notifymanager.notifyLL
        }

        SLTextInput {
            id: temp_edit
            width: 135
            enabled: checkBox.checked
            tooltip_fontfamily: fontmanager.curfont
            text: notifymanager.notifyTemp
            tooltip: qsTr("temp's alert value")
            anchors.left: comboBox.left
            anchors.leftMargin: 2
            anchors.verticalCenter: text2.verticalCenter
            Component.onCompleted:
                if(notifymanager.notifyTemp > 999)
                    temp_edit.text = ""
        }

        SLTextInput {
            id: humi_edit
            width: 135
            enabled: checkBox.checked
            tooltip_fontfamily: fontmanager.curfont
            text: notifymanager.notifyHumi
            tooltip: qsTr("humi's alert value")
            anchors.left: comboBox.left
            anchors.leftMargin: 2
            anchors.verticalCenter: text3.verticalCenter
            Component.onCompleted:
                if(notifymanager.notifyHumi > 999)
                    humi_edit.text = ""
        }

        Text {
            id: text1
            x: 30
            y: 50
            font.family: fontmanager.curfont
            text: qsTr("LL_ALERT:")
        }

        Text {
            id: text2
            text: qsTr("TEMP_ALERT:")
            font.family: fontmanager.curfont
            anchors.top: text1.bottom
            anchors.topMargin: 25
            anchors.left: text1.left
            anchors.leftMargin: 0
        }

        Text {
            id: text3
            text: qsTr("HUMI_ALERT:")
            font.family: fontmanager.curfont
            anchors.top: text2.bottom
            anchors.topMargin: 25
            anchors.left: text1.left
            anchors.leftMargin: 0
        }

        Button {
            id: btn_cancel
            width: 55
            height: 20
            text: qsTr("Cancel")
            anchors.verticalCenter: btn_save.verticalCenter
            anchors.right: btn_save.left
            anchors.rightMargin: 20
            onClicked: close()
        }

        Button {
            id: btn_save
            width: 55
            height: 20
            text: qsTr("Save")
            anchors.top: humi_edit.bottom
            anchors.topMargin: 18
            anchors.right: humi_edit.right
            anchors.rightMargin: 0
            onClicked: {
                if(!isNaN(parseInt(temp_edit.text)) && temp_edit.text.length != 0)
                    notifymanager.notifyTemp = Math.abs(parseInt(temp_edit.text))
                else if(!temp_edit.text.length)
                    temp_edit.text = notifymanager.notifyTemp
                if(!isNaN(parseInt(humi_edit.text)) && humi_edit.text.length != 0)
                    notifymanager.notifyHumi = Math.abs(parseInt(humi_edit.text))
                else if(!humi_edit.text.length)
                    humi_edit.text = notifymanager.notifyHumi
                notifymanager.notifyLL = comboBox.currentIndex
                notifymanager.notifyEnable = checkBox.checked
                close()
            }
        }
    }
}
