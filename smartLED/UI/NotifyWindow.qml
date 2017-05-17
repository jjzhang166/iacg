import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SLComponent 1.0

Window {
    id: notify_win
    visible: true
    width: 400
    height: 180
    title: qsTr("alertSetting")
    modality: Qt.ApplicationModal
    onClosing: {
        if(!isNaN(parseInt(temp_edit.text)))
            notifymanager.notifyTemp = parseInt(temp_edit.text)
        if(!isNaN(parseInt(humi_edit.text)))
            notifymanager.notifyHumi = parseInt(humi_edit.text)
        notifymanager.notifyLL = comboBox.currentIndex
        notifymanager.notifyEnable = checkBox.checked
    }

    CheckBox {
        id: checkBox
        x: 30
        y: 15
        text: qsTr("EnableNotify")
        checked: notifymanager.notifyEnable
    }

    ComboBox {
        id: comboBox
        enabled: checkBox.checked
        x: 182
        y: 49
        model: ["LL_H", "LL_MH", "LL_MEDIUM", "LL_LOW"]
        currentIndex: notifymanager.notifyLL
    }

    SLTextInput {
        id: temp_edit
        enabled: checkBox.checked
        x: 182
        y: 80
        tooltip_fontfamily: fontmanager.curfont
        text: notifymanager.notifyTemp
    }

    SLTextInput {
        id: humi_edit
        enabled: checkBox.checked
        x: 182
        y: 120
        tooltip_fontfamily: fontmanager.curfont
        text: notifymanager.notifyHumi
    }

    Text {
        id: text1
        x: 48
        y: 49
        text: qsTr("LL_ALERT:")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 48
        y: 80
        text: qsTr("TEMP_ALERT:")
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 48
        y: 120
        text: qsTr("HUMI_ALERT:")
        font.pixelSize: 12
    }
}
