import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    height: 460
    width: 525
    x: 200
    y: 30

    Button {
        id: button1
        x: 92
        y: 86
        width: 198
        height: 23
        text: qsTr("Button")
    }

    Button {
        id: button2
        x: 126
        y: 186
        width: 164
        height: 23
        text: qsTr("Button")
    }

    Button {
        id: button3
        x: 244
        y: 252
        width: 140
        height: 23
        text: qsTr("Button")
    }

    Button {
        id: button4
        x: 262
        y: 374
        width: 210
        height: 23
        text: qsTr("Button")
    }
}
