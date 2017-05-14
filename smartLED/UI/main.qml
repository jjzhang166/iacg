import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import SLComponent 1.0
import Manager.Serialport 1.0

Window {
    objectName: "obj_window1"
    id: window1
    visible: true
    width: 200
    height: 495
    color: "transparent"
    flags: Qt.FramelessWindowHint |
           Qt.WindowMinimizeButtonHint |
           Qt.Window

    function closeWinShadow() {
        winshadow.destroy()
    }

    DropShadow {
        id: winshadow
        anchors.fill: centerFrame
        fast: true
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8
        samples: 17
        spread: 0
        color: "#aa000000"
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
        x: 5
        z: 10
        width: parent.width - 10
        height: 30
        win_instance: window1
        title_opacity: 0
        onWidthChanged:
          title_opacity = width > 600 ? 1 : 0
    }

    property alias err_dia: _err_dia
    SLMsgDialog {
        id: _err_dia
        dia_title: qsTr("error")
        dia_icon_type: 1
        dia_text_leftmargin: 15
        dia_width: 270
        dia_content: qsTr("connect error")
    }

    Rectangle {
        id: centerFrame
        x: 5
        width: parent.width - 10
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
            property bool refresh
            id: comboBox1
            width: 170
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: text1.bottom
            anchors.topMargin: 10
            fontfamily: fontmanager.curfont
            refresh: pressed? true : false
            model: sc.portList
            Component.onCompleted:
                currentIndex = find(sc.portName)
            onRefreshChanged:
                if(refresh) {
                    sc.refreshPortlist()
                    model = sc.portList
                    if(sc.portList.length === 0)
                        currentIndex = -1
                }
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
                currentIndex = find(String(sc.baudRate))
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
                currentIndex = find(String(sc.dataBits))
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
                switch(sc.stopBits) {
                case SerialportManager.OneStop:
                    currentIndex = 0
                    break
                case SerialportManager.OneAndHalfStop:
                    currentIndex = 1
                    break
                case SerialportManager.TwoStop:
                    currentIndex = 2
                    break
                }
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
                switch(sc.parity) {
                case SerialportManager.NoParity:
                    currentIndex = 0
                    break
                case SerialportManager.OddParity:
                    currentIndex = 1
                    break
                case SerialportManager.EvenParity:
                    currentIndex = 2
                    break
                }
        }

        SLFlatButton {
            objectName: "obj_window1_button1"
            property var rightFrame: null
            property bool isConnected: false

            function initSerialportConnect() {
                if(!isConnected) {
                    sc.portName = comboBox1.currentText
                    sc.baudRate = Number(comboBox2.currentText)
                    sc.dataBits = Number(comboBox3.currentText)
                    sc.stopBits = (comboBox4.currentIndex == 0? SerialportManager.OneStop:
                                    comboBox4.currentIndex == 1? SerialportManager.OneAndHalfStop:
                                        SerialportManager.TwoStop)
                    sc.parity = (comboBox5.currentIndex == 0? SerialportManager.NoParity:
                                    comboBox5.currentIndex == 1?SerialportManager.OddParity:
                                        SerialportManager.EvenParity)
                    if(sc.connectSart()) {
                        window1.width = 730
                        isConnected = true
                        button1.text = qsTr("DisConnect")
                        var comRf = Qt.createComponent("qrc:/UI/RightFrame.qml")
                        if (comRf.status === Component.Ready)
                            rightFrame = comRf.createObject(window1)
                        return true
                    }
                    else
                        return false
                }
                else {
                    window1.width = 200
                    isConnected = false
                    rightFrame.destroy()
                    button1.text = qsTr("Connect")
                    sc.connectStop()
                    return true
                }
            }

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
                if(!initSerialportConnect())
                    window1.err_dia.open()
            }
        }
    }
}
