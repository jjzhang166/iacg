﻿import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import SLComponent 1.0
import Manager.Mail 1.0
import Manager.Serialport 1.0

Rectangle {
    property string bg_color: "#fafafa"
    property int humi_time: 0
    property int temp_time: 0
    property int delay_time: 60
    id: rectangle1
    width: 525
    height: 430

    Connections {
        target: maildata
        onCollData: {
            con.temp_busy = true
            con.humi_busy = true
        }
        onCollTempEnd: {
            if(res == MailManager.ERR_SUCCESS) {
                console.log("coll temp end,and send mail stand by")
                con.temp_busy = false
            }
        }
        onCollHumiEnd: {
            if(res == MailManager.ERR_SUCCESS) {
                console.log("coll humi end,and send mail stand by")
                con.humi_busy =false
            }
        }
    }

    Connections {
        id: con
        property bool temp_busy: false
        property bool humi_busy: false
        target: sc
        onTempChanged: {
            tm = parseInt("0x"+tm)
            if(!con.temp_busy) {
                if(maildata.tmpAlert != -1 && tm > maildata.tmpAlert) {
                    if(temp_time == 0) {
                        temp_time = maildata.getCurTimeSec()
                        maildata.sendMail(MailManager.MAIL_TMP)
                        return
                    }
                    if(maildata.getCurTimeSec() - temp_time > delay_time) {
                        temp_time = maildata.getCurTimeSec()
                        maildata.sendMail(MailManager.MAIL_TMP)
                    }
                }
            }
            temp_value.text = tm
            temp_gauge.value = tm
        }

        onHumiChanged: {
            hm = parseInt("0x"+hm)
            if(!con.humi_busy) {
                if(maildata.humiAlert != -1 && hm > maildata.humiAlert) {
                    if(humi_time == 0) {
                        humi_time = maildata.getCurTimeSec()
                        maildata.sendMail(MailManager.MAIL_HUMI)
                        return
                    }
                    if(maildata.getCurTimeSec() - humi_time > delay_time) {
                        humi_time = maildata.getCurTimeSec()
                        maildata.sendMail(MailManager.MAIL_HUMI)
                    }
                }
            }
            humi_value.text = hm
            humi_gauge.value = hm
        }

        onLightChanged: {
            switch(ll) {
            case 0:             //LL_HIGH
                light_img.source = "qrc:/pic/light_h.png"
                break
            case 1:             //LL_MH
                light_img.source = "qrc:/pic/light_mh.png"
                break
            case 2:             //LL_MEDIUM
                light_img.source = "qrc:/pic/light_m.png"
                break
            case 3:             //LL_LOW
                light_img.source = "qrc:/pic/light_l.png"
            }
        }
    }

    Rectangle {
        id: light_panel
        color: bg_color
        width: parent.width / 2
        height: parent.height / 2
        Text {
            id: light_label
            text: qsTr("CurrentLight:")
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }

        Image {
            id: light_img
            width: 100
            height: 100
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: light_label.bottom
            anchors.topMargin: 25
            source: "qrc:/pic/light_h.png"
        }
    }

    Rectangle {
        id: temp_panel
        color: bg_color
        width: parent.width / 2
        height: parent.height / 2
        anchors.left: light_panel.right
        anchors.leftMargin: 0
        Text {
            id: temp_label
            text: qsTr("CurrentTemp:")
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }

        Text {
            id: temp_value
            text: qsTr("0")
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: temp_label.bottom
            anchors.topMargin: 30
            font.family: fontmanager.curfont
            font.pixelSize: 75
        }

        SLGauge {
            id: temp_gauge
            value: 0
            height: 160
            normal_color: "red"
            alert_color: "red"
            anchors.verticalCenterOffset: 5
            anchors.horizontalCenterOffset:70
            anchors.right: parent.right
            anchors.rightMargin: -140
        }

        Text {
            x: 135
            y: 65
            text: qsTr("℃")
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }
    }

    Rectangle {
        id: humi_panel
        color: bg_color
        width: parent.width / 2
        height: parent.height / 2
        anchors.top: light_panel.bottom
        anchors.topMargin: 0
        Text {
            id: humi_label
            text: qsTr("CurrentHumi:")
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }

        Text {
            id: humi_value
            text: qsTr("0")
            anchors.left: parent.left
            anchors.leftMargin: 45
            anchors.top: humi_label.bottom
            anchors.topMargin: 30
            font.family: fontmanager.curfont
            font.pixelSize: 75
        }

        SLGauge {
            id: humi_gauge
            height: 160
            value: 0
            tickmarkStepSize: 20
            maximumValue: 150
            minimumValue: 10
            minorTickmarkCount: 1
            normal_color: "blue"
            alert_color: "blue"
            anchors.verticalCenterOffset: 2
            anchors.horizontalCenterOffset:61
            anchors.right: parent.right
            anchors.rightMargin: -155
        }

        Text {
            x: 118
            y: 60
            text: qsTr("%RH")
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }
    }

    Rectangle {
        id: setting_panel
        color: bg_color
        width: parent.width / 2
        height: parent.height / 2
        anchors.left: humi_panel.right
        anchors.leftMargin: 0
        anchors.top: temp_panel.bottom
        anchors.topMargin: 0
        Text {
            id: setting_label
            text: qsTr("SendDelay:")
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 25
            font.family: fontmanager.curfont
            font.pixelSize: 15
        }

        SLCheckBox {
            id: checkBox1
            text: qsTr("Default Time")
            fontfamily: fontmanager.curfont
            checked: true
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: setting_label.bottom
            anchors.topMargin: 20
        }

        Text {
            id: text1
            enabled: !checkBox1.checked
            text: qsTr("Custom Time:")
            color: text1.enabled?"black":"gray"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: checkBox1.bottom
            anchors.topMargin: 15
            font.family: fontmanager.curfont
            font.pixelSize: 13
        }

        SLComboBox {
            id: comboBox1
            enabled: !checkBox1.checked
            width: 135
            anchors.left: text1.right
            anchors.leftMargin: 10
            anchors.top: checkBox1.bottom
            anchors.topMargin: 11
            fontfamily: fontmanager.curfont
            model: [qsTr("5 minute"),qsTr("15 minutes"),
                qsTr("1 hour"),qsTr("10 hours"),qsTr("24 hours")]
        }

        SLFlatButton {
            id: button1
            width: 220
            height: 23
            text: qsTr("OK")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: comboBox1.bottom
            anchors.topMargin: 27
            fontfamily: fontmanager.curfont
            onClicked: {
                if(checkBox1.checked)
                    rectangle1.delay_time = 60
                else {
                    rectangle1.delay_time =
                            comboBox1.currentIndex == 0? 300:
                            comboBox1.currentIndex == 1? 900:
                            comboBox1.currentIndex == 2? 3600:
                            comboBox1.currentIndex == 3? 36000:
                                                         86400
                    //console.log("cur delay time:"+rectangle1.delay_time)
                }
            }
        }
    }

    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 1
            ctx.strokeStyle = "gray"
            ctx.beginPath()
            ctx.moveTo(0,0)
            ctx.lineTo(0,parent.height)
            ctx.moveTo(90,parent.height/2)
            ctx.lineTo(parent.width-90,parent.height/2)
            ctx.moveTo(parent.width/2,90)
            ctx.lineTo(parent.width/2,parent.height-90)
            ctx.closePath()
            ctx.stroke()
        }
    }
}
