/*
*time:      2017/1/4
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: TabView
*/

import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TabView {
    id: tv
    property int tab_width: 110
    property int tab_height: 30
    
    style: TabViewStyle {
      frameOverlap: 1
      tab: Rectangle {
        implicitWidth: tv.tab_width
        implicitHeight: tv.tab_height
        color: styleData.selected ? "gray" :"transparent"
        border.color:  "gray"
        border.width: styleData.hovered? 2 : 1
        Text {
            id: text
            anchors.centerIn: parent
            text: styleData.title
            color: styleData.selected ? "white" : "black"
        }
      }
      frame: Rectangle { color: "transparent" }
    }
}
