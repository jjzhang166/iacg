import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    property var win_instance: null
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
            anchors.verticalCenterOffset: -3
            anchors.right: btn_close.left
            anchors.rightMargin: 7
            anchors.verticalCenter: parent.verticalCenter
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
    }
}
