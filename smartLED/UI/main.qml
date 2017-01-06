import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import SLComponent 1.0

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

        SLComboBox {
            id: comboBox1
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text1.bottom
            anchors.topMargin: 10
            model: ["COM0","COM1","COM2","COM3","COM4",
            "COM5","COM6","COM7","COM8","COM9","COM10",
            "COM11","COM12","COM13","COM14","COM15"]
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

        SLComboBox {
            id: comboBox2
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text2.bottom
            anchors.topMargin: 10
            currentIndex: 3
            model: [1200,2400,4800,9600,
            19200,38400,57600,115200]
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

        SLComboBox {
            id: comboBox3
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text3.bottom
            anchors.topMargin: 10
            currentIndex: 3
            model: [5,6,7,8]
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

        SLComboBox {
            id: comboBox4
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text4.bottom
            anchors.topMargin: 10
            model: ["1","1.5","2"]
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

        SLComboBox {
            id: comboBox5
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text5.bottom
            anchors.topMargin: 10
            model: ["No","Odd","Even"]
        }

        SLFlatButton {
            property var rightFrame: null
            property bool isConnected: false
            id: button1
            width: 160
            text: qsTr("Connect")
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                if(!isConnected) {
                    sc.portName = comboBox1.currentText
                    sc.setBaudRate(Number(comboBox2.currentText))
                    sc.setDataBits(Number(comboBox3.currentText))
                    sc.setStopBits(comboBox4.currentIndex == 0?sc.OneStop:
                                    comboBox4.currentIndex == 1?sc.OneAndHalfStop:
                                        sc.TwoStop)
                    sc.setParity(comboBox5.currentIndex == 0?sc.NoParity:
                                    comboBox5.currentIndex == 1?sc.OddParity:
                                        sc.EvenParity)
                    if(sc.connectSart()) {
                        window1.width = 730
                        isConnected = true
                        button1.text = qsTr("DisConnect")
                        var comRf = Qt.createComponent("qrc:/UI/RightFrame.qml")
                        if (comRf.status === Component.Ready)
                            rightFrame = comRf.createObject(window1)

                    }
                    else {
                        var comDialog = Qt.createComponent("qrc:/UI/MsgDialog.qml")
                        if(comDialog.status === Component.Ready)
                            comDialog.createObject(window1)
                        return
                    }
                }
                else {
                    window1.width = 200
                    isConnected = false
                    rightFrame.destroy()
                    button1.text = qsTr("Connect")
                    sc.connectStop()
                }
            }
        }
    }
}
