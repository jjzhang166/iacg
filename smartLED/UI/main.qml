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

    //handle font changed
    Connections {
        target: fontmanager
        onCurfontChanged: {
            text1.font.family = fontmanager.curfont
            text2.font.family = fontmanager.curfont
            text3.font.family = fontmanager.curfont
            text4.font.family = fontmanager.curfont
            text5.font.family = fontmanager.curfont
        }
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
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox1
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text1.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            model: [sc.portList[0],sc.portList[1],sc.portList[2],
            sc.portList[3],sc.portList[4],sc.portList[5],
            sc.portList[6],sc.portList[7]]
            Component.onCompleted:
                currentIndex = find(sc.curPortName)
        }

        Text {
            id: text2
            text: qsTr("BaudRate:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox1.bottom
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox2
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text2.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            model: [1200,2400,4800,9600,
            19200,38400,57600,115200]
            Component.onCompleted:
                currentIndex=find(String(sc.curBaudRate))
        }

        Text {
            id: text3
            text: qsTr("DataBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox2.bottom
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox3
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text3.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            model: [5,6,7,8]
            Component.onCompleted:
                currentIndex=find(String(sc.curDataBit))
        }

        Text {
            id: text4
            text: qsTr("StopBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox3.bottom
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox4
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text4.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            model: ["1","1.5","2"]
            Component.onCompleted:
                currentIndex=find(sc.curStopBit)
        }

        Text {
            id: text5
            text: qsTr("CheckBit:")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: comboBox4.bottom
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox5
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text5.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            model: ["No","Odd","Even"]
            Component.onCompleted:
                currentIndex=find(sc.curParity)
        }

        SLFlatButton {
            property var rightFrame: null
            property bool isConnected: false
            id: button1
            width: 160
            height: 28
            text: qsTr("Connect")
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            fontfamily: fontmanager.curfont
            onClicked: {
                if(!isConnected) {
                    sc.portName = comboBox1.currentText
                    sc.setBaudRate(Number(comboBox2.currentText))
                    sc.setDataBits(Number(comboBox3.currentText))
                    sc.setStopBits(comboBox4.currentIndex == 0? 1:
                                    comboBox4.currentIndex == 1?3:
                                        2)
                    sc.setParity(comboBox5.currentIndex == 0? 0:
                                    comboBox5.currentIndex == 3?sc.OddParity:
                                        2)
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
