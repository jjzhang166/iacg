/*
*time:      2017/2/14
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: Message Dialog
*/

import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Dialog {
	property string dia_title: "smartLED dialog"
	property string dia_content: "SmartLED project component: Message Dialog"
	property int	dia_icon_type: 0		//set 0 to use "info.png",else use "error.png"
	property int 	dia_text_leftmargin: 5
	property int    dia_text_vcenter_offset: -20
	property string btn_text: "OK"
	property int dia_width: 363
	property int dia_height: 100
	property Component dia_icon: Image {
		source: dia_icon_type == 0 ? 
					"./res/info.png" : "./res/error.png"
	}
	property int btn_width: 100
	property int btn_height: 30
	
	id: dia
	title: dia_title
	modality: Qt.ApplicationModal
	contentItem: Rectangle {
		color: "#fafafa"
		implicitWidth: dia.dia_width
		implicitHeight: dia.dia_height
		Loader {
			id: img_loader
			anchors.left: parent.left
			anchors.leftMargin: 20
			anchors.top: parent.top
			anchors.topMargin: 10
			sourceComponent: dia.dia_icon
		}

		Text {
			text: dia.dia_content
			color: "black"
			anchors.verticalCenter: parent.verticalCenter
			anchors.verticalCenterOffset: dia.dia_text_vcenter_offset
			anchors.left: img_loader.right
			anchors.leftMargin: dia.dia_text_leftmargin
		}

		Button {
			text: dia.btn_text
			width: dia.btn_width
			anchors.right: parent.right
			anchors.rightMargin: 15
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 15
			onClicked: dia.close()
		}
	}
}