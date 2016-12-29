import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id: window1
    visible: true
    width: 460
    height: 278
    flags: "Window | FramelessWindowHint"

    Image {
        anchors.fill: parent
        source: "qrc:/pic/bugreport_background.png"
    }

    MouseArea{
        property point clickPos: "0,0"
        anchors.fill: parent
        onPressed: clickPos = Qt.point(mouse.x,mouse.y);
                    onPositionChanged: {
                        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y);
                        window1.setX(window1.x+delta.x);
                        window1.setY(window1.y+delta.y);
        }
    }

    Button {
        id: button1
        width: 120
        text: qsTr("Close")
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                color: control.pressed || control.hovered? "gray" : "transparent"
                opacity: control.pressed? 1 :
                         control.hovered? 0.5 : 1
                border.width: 2
                border.color: "gray"
                radius: 4
            }
        }
        onClicked: Qt.quit()
    }

    Text {
        id: text2
        width: 175
        height: 65
        text: qsTr(argdes)
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignTop
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: label1.bottom
        anchors.topMargin: 5
        font.pixelSize: 15
    }

    Label {
        id: label1
        text: qsTr("ErrorCode:")
        font.pointSize: 13
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 140
    }

    Label {
        id: label2
        text: qsTr(argcode)
        anchors.bottom: label1.top
        anchors.bottomMargin: -17
        font.pointSize: 13
        anchors.left: parent.left
        anchors.leftMargin: 120
    }

    Image {
        id: image1
        width: 219
        height: 17
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 100
        source: "qrc:/pic/errmsg.png"
    }
}
