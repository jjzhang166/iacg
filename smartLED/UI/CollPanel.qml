import QtQuick 2.4
import SLComponent 1.0

Rectangle {
    property string bg_color: "#fafafa"
    id: rectangle1
    width: 525
    height: 430

    Connections {
        target: sc
        onTempChanged: {
            tm = parseInt("0x"+tm)
            if(tm > 30)
                temp_value.color = "red"
            temp_value.text = tm
            temp_gauge.value = tm
        }

        onHumiChanged: {
            hm = parseInt("0x"+hm)
            humi_value.text = hm
            humi_gauge.value = hm
        }

        onLightChanged: {
            lg = parseInt("0x"+lg)
            console.log("light:" + lg)
            if(lg > 230)
                light_img.source = "qrc:/pic/light_l.png"
            else if(lg > 140)
                light_img.source = "qrc:/pic/light_m.png"
            else if(lg > 100)
                light_img.source = "qrc:/pic/light_mh.png"
            else
                light_img.source = "qrc:/pic/light_h.png"
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
            font.pixelSize: 15
        }

        Text {
            id: temp_value
            text: qsTr("0")
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: temp_label.bottom
            anchors.topMargin: 30
            font.pixelSize: 75
        }

        SLGauge {
            id: temp_gauge
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
            font.pixelSize: 15
        }

        Text {
            id: humi_value
            text: qsTr("0")
            anchors.left: parent.left
            anchors.leftMargin: 45
            anchors.top: humi_label.bottom
            anchors.topMargin: 30
            font.pixelSize: 75
        }

        SLGauge {
            id: humi_gauge
            height: 160
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
            id: text1
            x: 118
            y: 60
            text: qsTr("%RH")
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
