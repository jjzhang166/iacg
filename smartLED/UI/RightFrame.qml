﻿import QtQuick 2.0
import QtQuick.Controls 1.4

import SLComponent 1.0

Rectangle {
    property var serialInstance
    height: 460
    width: 525
    x: 200
    y: 30

    SLTabView {
        id: tv
        tab_width: 130
        anchors.fill: parent
        Tab {
            title: "mainMenu"
            CollPanel {
                serial_instance: serialInstance
            }
        }
        Tab {
            title: "about"
            Rectangle { color: "green" }
        }
    }
}
