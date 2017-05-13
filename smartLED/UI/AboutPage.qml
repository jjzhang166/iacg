import QtQuick 2.0

Rectangle {
    id: rectangle1
    width: 525
    height: 430

    Image {
        id: image1
        width: 402
        height: 77
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        source: "qrc:/pic/project_logo.png"
    }

    Text {
        id: text1
        x: 50
        y: 150
        text: qsTr("Project:SmartLED")
        font.family: fontmanager.curfont
        font.pointSize: 13
    }

    Text {
        id: text2
        x: 50
        text: qsTr("Author:dengjunkai")
        font.family: fontmanager.curfont
        font.pointSize: 13
        anchors.top: text1.bottom
        anchors.topMargin: 30
    }

    Text {
        id: text3
        x: 50
        text: qsTr("Author's School Home:")
        anchors.top: text2.bottom
        anchors.topMargin: 30
        font.pointSize: 13
        font.family: fontmanager.curfont
    }

    Text {
        id: text4
        y: 244
        text: "<html></style>
                <a href=\"http://www.nxist.com\">
                www.nxist.com</a>
                </html>"
        anchors.left: text3.right
        anchors.leftMargin: 6
        font.family: fontmanager.curfont
        font.pointSize: 13
        onLinkActivated: Qt.openUrlExternally(link)
        MouseArea {
            id: m1
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
            onEntered: m1.cursorShape = Qt.PointingHandCursor
            onExited: m1.cursorShape = Qt.ArrowCursor
        }
    }

    Text {
        id: text5
        x: 50
        text: qsTr("EMail:linuxlike@foxmail.com")
        anchors.top: text4.bottom
        anchors.topMargin: 30
        font.pointSize: 13
        font.family: fontmanager.curfont
    }
}
