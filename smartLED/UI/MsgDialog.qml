import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

import SLComponent 1.0

Window {
    id: msgdia
    visible: true
    width: 300
    height: 120
    modality: Qt.ApplicationModal
    flags: Qt.Dialog | Qt.FramelessWindowHint
    color: "#f6f6f8"
    TopFrame {
        z: 10
        width: parent.width
        height: 30
        win_instance: msgdia
    }

    Image {
        id: image1
        width: 72
        height: 72
        anchors.left: parent.left
        anchors.leftMargin: 22
        anchors.verticalCenterOffset: 12
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/pic/error.png"
    }

    Text {
        id: text1
        width: 160
        height: 35
        text: qsTr("ConnectError,Need a right SerialPort")
        wrapMode: Text.WordWrap
        anchors.verticalCenterOffset: -18
        anchors.left: image1.right
        anchors.leftMargin: 17
        anchors.verticalCenter: image1.verticalCenter
        font.pixelSize: 15
    }

    SLFlatButton {
        id: button1
        width: 160
        height: 23
        text: qsTr("OK")
        anchors.left: parent.left
        anchors.leftMargin: 111
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        onClicked: msgdia.close()
    }
}
