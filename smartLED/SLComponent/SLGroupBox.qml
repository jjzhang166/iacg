/*
*time:      2017/1/29
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: Gauge 
*/

import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    property string title: "Title"
    property string titleColor: "black"
    property string segmentLineColor: "#B3B3B3"				
    property int titleTopMargin: 10
    property int titleLeftMargin: 25
    property int titleFontSize: 25
	property string fontfamily: ""
    property Component content: Rectangle {
        anchors.fill: parent
        color: "gray"
    }

    implicitHeight: 100
    implicitWidth: 100

    Text {
        id: text_title
        text: qsTr(parent.title)
        anchors.left: parent.left
        anchors.leftMargin: parent.titleLeftMargin
        anchors.top: parent.top
        anchors.topMargin: parent.titleTopMargin
		font.family: fontfamily
        font.pixelSize: parent.titleFontSize
        color: parent.titleColor
    }

    Loader {
        id: content_loader
        width: parent.width
        anchors.bottom: canv.top
        anchors.bottomMargin: 0
        anchors.top: text_title.bottom
        anchors.topMargin: 0
        sourceComponent: parent.content
    }

    Canvas {
        id: canv
        width: parent.width
        height: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 1
            ctx.strokeStyle = parent.segmentLineColor
            ctx.beginPath()
            ctx.moveTo(parent.width*0.05, 5)
            ctx.lineTo(parent.width*0.95, 5)
            ctx.closePath()
            ctx.stroke()
        }
    }
}
