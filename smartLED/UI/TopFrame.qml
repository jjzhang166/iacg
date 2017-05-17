import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    property var win_instance: null
    property alias title_opacity: topFrame.app_title_opacity
    property alias notify_opacity: topFrame.btn_notify_opacity

    Rectangle {
        id: topFrame
        anchors.fill: parent
        color: "#3f3f3f"

        MouseArea {
            property point clickPos: "0,0"
            anchors.fill: topFrame
            onPressed: clickPos = Qt.point(mouse.x,mouse.y);
                        onPositionChanged: {
                            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y);
                            win_instance.setX(win_instance.x+delta.x);
                            win_instance.setY(win_instance.y+delta.y);
            }
        }

        Image {
            id: app_icon
            width: 18
            height: 18
            anchors.left: parent.left
            anchors.leftMargin: 7
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/sl.ico"
        }

        property alias app_title_opacity: app_title.opacity
        Text {
            id: app_title
            width: 30
            height: 18
            anchors.left: app_icon.right
            anchors.leftMargin: 7
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 3
            font.family: fontmanager.curfont
            color: "#ffffff"
            text: qsTr("The SmartLED Project")
        }

        Image {
            id: btn_close
            width: 14
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/pic/Close.png"
            MouseArea {
                z: 10
                anchors.fill: parent
                hoverEnabled: true
                onEntered: btn_close.source = "qrc:/pic/CloseHover.png"
                onExited: btn_close.source = "qrc:/pic/Close.png"
                onClicked: win_instance.close()
            }
        }

        Image {
            id: btn_min
            width: 14
            height: 14
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -3
            anchors.right: btn_close.left
            anchors.rightMargin: 7
            source: "qrc:/pic/Minimize.png"
            MouseArea {
                z: 10
                anchors.fill: parent
                hoverEnabled: true
                onEntered: btn_min.source = "qrc:/pic/MinimizeHover.png"
                onExited: btn_min.source = "qrc:/pic/Minimize.png"
                onClicked: win_instance.showMinimized()
            }
        }

        property alias btn_notify_opacity: btn_notify.opacity
        Image {
            id: btn_notify
            width: 14
            height: 14
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: btn_min.left
            anchors.rightMargin: 7
            source: "qrc:/pic/notify.png"
            MouseArea {
                z: 10
                anchors.fill: parent
                hoverEnabled: true
                onEntered: btn_notify.source = "qrc:/pic/notify_hover.png"
                onExited: btn_notify.source = "qrc:/pic/notify.png"
                onClicked: {
                    var notifywin = Qt.createComponent("qrc:/UI/NotifyWindow.qml")
                    if(notifywin.status === Component.Ready)
                        notifywin.createObject()
                }
            }
        }
    }
}
