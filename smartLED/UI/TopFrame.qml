import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    property var win_instance: null
    Rectangle {
        id: topFrame
        anchors.fill: parent
        color: "#3f3f3f"
    }

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
}
