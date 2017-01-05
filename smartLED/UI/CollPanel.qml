import QtQuick 2.0

Rectangle {
    property var serial_instance
    id: rectangle1
    width: 525
    height: 430

    Connections {
        target: serial_instance
        onTempChanged: {
            temp_value.text = parseInt("0x"+tm)
        }

        onHumiChanged: {
            humi_value.text = parseInt("0x"+hm)
        }

        onLightChanged: {
            lg = parseInt("0x"+lg)
            console.log("light:" + lg)
            if(lg > 230)
                light_img.source = "qrc:/pic/light_l.png"
            else if(lg > 100)
                light_img.source = "qrc:/pic/light_m.png"
            else
                light_img.source = "qrc:/pic/light_h.png"
        }
    }

    Rectangle {
        id: light_panel
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

        Image {
            id: image2
            width: 100
            height: 100
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: temp_label.bottom
            anchors.topMargin: 25
            source: "../pic/light_h.png"
        }

        Text {
            id: temp_value
            text: qsTr("0")
            anchors.verticalCenter: temp_label.verticalCenter
            anchors.left: temp_label.right
            anchors.leftMargin: 20
            font.pixelSize: 35
        }
    }

    Rectangle {
        id: humi_panel
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

        Image {
            id: image3
            width: 100
            height: 100
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: humi_label.bottom
            anchors.topMargin: 25
            source: "../pic/light_h.png"
        }

        Text {
            id: humi_value
            text: qsTr("0")
            anchors.verticalCenter: humi_label.verticalCenter
            anchors.left: humi_label.right
            anchors.leftMargin: 20
            font.pixelSize: 36
        }
    }

    Rectangle {
        id: setting_panel
        width: parent.width / 2
        height: parent.height / 2
        anchors.left: humi_panel.right
        anchors.leftMargin: 0
        anchors.top: temp_panel.bottom
        anchors.topMargin: 0
    }
}
