import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 950
    height: 600

    Rectangle {
        id: win
        anchors.fill: parent
        color: "#f6f6f8"
    }

    Image {
        id: image1
        x: 650
        y: 300
        source: "qrc:/ilogo.png"
    }
}
