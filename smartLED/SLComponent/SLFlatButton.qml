/*
*time:      2017/1/3
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: FlatButton 
*/

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
    property string pressed_color: "#e1e1e1"
    property string unpressed_color: "transparent"
    property string border_color: "gray"
    property int hovered_borderwidth: 2
    property int unhovered_borderwidth: 1

    id: btn
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 30
            implicitWidth: 100
            color: control.pressed? btn.pressed_color : btn.unpressed_color
            border.width: control.hovered? btn.hovered_borderwidth :
                                           btn.unhovered_borderwidth
            border.color: btn.border_color
        }
    }
}
