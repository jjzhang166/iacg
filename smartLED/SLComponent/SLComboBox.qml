/*
*time:      2017/1/3
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: ComboBox 
*/

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0

ComboBox {
    implicitWidth: 160
    implicitHeight: 25
    
    style: ComboBoxStyle {
        background: Rectangle {
            implicitWidth: 160
            implicitHeight: 25
            color: "transparent"
            border.color: "gray"
            border.width: control.hovered || control.pressed? 2 : 1
            Image {
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                source: control.hovered? "./res/Down.png" : "./res/DownHover.png"
            }
        }
        // drop-down customization here
        property Component __dropDownStyle: MenuStyle {
            __maxPopupHeight: 600
            __menuItemType: "comboboxitem"

            frame: Rectangle {              // background
                color: "white"
                border.width: 1
                border.color: "gray"
            }

            itemDelegate.background: Rectangle {  // selection of an item
                color: styleData.selected ? "darkGray" : "transparent"
            }

            __scrollerStyle: ScrollViewStyle { }
        }
    }
}
