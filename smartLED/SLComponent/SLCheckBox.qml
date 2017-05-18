/*
*time:      2017/1/7
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: CheckBox 
*/

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {
	property string fontfamily: "Times New Roman"
	property string fontcolor: "black"
	
    style: CheckBoxStyle {
        spacing: 15
        background: Rectangle {
            color: "transparent"
        }

        label: Text {
            text: control.text
            color: fontcolor
			font.family: fontfamily
        }
        
        indicator: Rectangle {
            implicitWidth: 16
            implicitHeight: 16
            border.color: "#e1e1e1"
            border.width: 1
            Rectangle {
                visible: control.hovered
                color: "#e1e1e1"
                opacity: 0.9
                anchors.margins: 4
                anchors.fill: parent
            }

            Rectangle {
                visible: control.checked
                color: "gray"
                anchors.margins: 4
                anchors.fill: parent
            }
        }
    }
}