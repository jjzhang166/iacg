import QtQuick 2.4
import QtQuick.Controls 1.4

/*
*time:      2017/1/29
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: TextInput
*/

TextInput {
    property string tooltip: "text"
	property string tooltip_fontfamily: ""
	
    id: textInput
    width: 80
    height: 15
    selectByMouse: true
    selectionColor: "gray"
    font.pixelSize: 14
    onLengthChanged: {
        if(length > 0)
            tooltip.opacity = 0
        else
            tooltip.opacity = 0.7
    }

    Text {
        id: tooltip
        anchors.fill: parent
        text: qsTr(parent.tooltip)
		font.family: tooltip_fontfamily
        font.pixelSize: 14
        opacity: 0.7
        color: "gray"
    }

    Rectangle {
        id: frame
        anchors.fill: parent
        color: "transparent"
        anchors.leftMargin: -2
        anchors.topMargin: -2
        border.color: "gray"
        border.width: 1
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
            onEntered:
                cursorShape = Qt.IBeamCursor
        }
    }
}
