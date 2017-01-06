/*
*time:      2017/1/6
*author:    linuxlike
*email:     linuxlike@foxmail.com
*SmartLED project component: Gauge 
*/

import QtQuick 2.4
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Gauge {
    id: gauge
    property int threshold: 30
    property string normal_color: "blue"
    property string alert_color: "red"

    height: 200
    minimumValue: 0
    maximumValue: 50
    value: 15
    anchors.centerIn: parent
    style: GaugeStyle {
        background: Rectangle {
            implicitWidth: 12
            border.width: 1
            border.color: "gray"
        }

        valueBar: Rectangle {
            implicitWidth: 14
            color: gauge.value > gauge.threshold ?
                       gauge.alert_color : gauge.normal_color
        }

        tickmarkLabel: Item {
            implicitWidth: 17
            implicitHeight: 13
            Text {
                color: "black"
                text:   styleData.value >= 100? styleData.value
                        : styleData.value === 0? "  " + styleData.value
                        :" " + styleData.value
            }
        }

        tickmark: Item {
            implicitWidth: 15
            implicitHeight: 1

            Rectangle {
                color: "black"
                anchors.fill: parent
                anchors.leftMargin: 3
                anchors.rightMargin: 3
            }
        }

        minorTickmark: Item {
            implicitWidth: 8
            implicitHeight: 1

            Rectangle {
                color: "black"
                anchors.fill: parent
                anchors.leftMargin: 2
                anchors.rightMargin: 4
            }
        }
    }
}