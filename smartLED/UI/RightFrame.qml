import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    property var serialInstance: null
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
        text: qsTr("WriteA")
        onClicked: serialInstance.writeChar('a')
    }

    Button {
        id: button2
        x: 126
        y: 186
        width: 164
        height: 23
        text: qsTr("WriteB")
        onClicked: {
            serialInstance.writeChar('b')
            console.log("write B")
        }
    }

    Button {
        id: button3
        x: 244
        y: 252
        width: 140
        height: 23
        text: qsTr("WriteC")
        onClicked: serialInstance.writeChar("c");
    }

    Button {
        id: button4
        x: 262
        y: 374
        width: 210
        height: 23
        text: qsTr("WriteByte")
        onClicked: serialInstance.writeByte("f1");
    }
}
