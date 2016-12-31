import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Window {
    id: window1
    visible: true
    width: 200
    height: 495
    color: "transparent"
    flags: 0x0800 | 0x0001

    DropShadow {
        anchors.fill: centerFrame
        fast: true
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8
        samples: 17
        color: "#80000000"
        source: centerFrame
    }

    TopFrame {
        id: tf
        z: 10
        width: parent.width - 5
        height: 30
        win_instance: window1
    }

    Rectangle {
        id: centerFrame
        width: parent.width - 5
        height: parent.height - 5
        color: "#f6f6f8"

        Text {
            id: text1
            text: qsTr("SerialPort:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 45
            font.pixelSize: 13
        }

        ComboBox {
            id: comboBox1
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text1.bottom
            anchors.topMargin: 10
        }

        Text {
            id: text2
            text: qsTr("BaudRate:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox1.bottom
            anchors.topMargin: 25
            font.pixelSize: 13
        }

        ComboBox {
            id: comboBox2
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text2.bottom
            anchors.topMargin: 10
        }

        Text {
            id: text3
            text: qsTr("DataBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox2.bottom
            anchors.topMargin: 25
            font.pixelSize: 13
        }

        ComboBox {
            id: comboBox3
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text3.bottom
            anchors.topMargin: 10
        }

        Text {
            id: text4
            text: qsTr("StopBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox3.bottom
            anchors.topMargin: 25
            font.pixelSize: 13
        }

        ComboBox {
            id: comboBox4
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text4.bottom
            anchors.topMargin: 10
        }

        Text {
            id: text5
            text: qsTr("CheckBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox4.bottom
            anchors.topMargin: 25
            font.pixelSize: 13
        }

        ComboBox {
            id: comboBox5
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text5.bottom
            anchors.topMargin: 10
        }

        Button {
            property var rightFrame: null
            property bool isClicked: false
            id: button1
            width: 160
            text: qsTr("Connect")
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                if(!isClicked) {
                    window1.width = 730
                    isClicked = true
                    var com = Qt.createComponent("qrc:/UI/RightFrame.qml")
                    if (com.status === Component.Ready)
                        rightFrame = com.createObject(window1)
                }
                else {
                    window1.width = 200
                    isClicked = false
                    rightFrame.destroy()
                }
            }
        }
    }
}
