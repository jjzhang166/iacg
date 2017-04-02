import QtQuick 2.0

Rectangle {
    id: rectangle1
    width: 525
    height: 430

    Image {
        id: image1
        width: 417
        height: 39
        anchors.top: parent.top
        anchors.topMargin: 55
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/pic/project_logo.png"
    }

    Text {
        id: text1
        x: 54
        y: 133
        text: qsTr("Author:linuxlike")
        font.family: fontmanager.curfont
        font.pointSize: 13
    }

    Text {
        id: text2
        x: 54
        text: qsTr("EMail:linuxlike@foxmail.com")
        font.family: fontmanager.curfont
        font.pointSize: 13
        anchors.top: text1.bottom
        anchors.topMargin: 30
    }

    Text {
        id: text3
        x: 54
        text: qsTr("ProjectHome:")
        anchors.top: text2.bottom
        anchors.topMargin: 30
        font.pointSize: 13
        font.family: fontmanager.curfont
    }

    Text {
        id: text4
        y: 227
        text: "<html></style>
                <a href=\"https://git.oschina.net/linuxlike/iacg\">
                git.oschina.net/linuxlike/iacg</a>
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
        x: 54
        text: qsTr("Author's School Home:")
        anchors.top: text4.bottom
        anchors.topMargin: 30
        font.pointSize: 13
        font.family: fontmanager.curfont
    }

    Text {
        id: text6
        y: 274
        text: "<html></style>
                <a href=\"http://www.nxist.com\">
                nxist.com</a>
                </html>"
        anchors.left: text5.right
        anchors.leftMargin: 6
        font.family: fontmanager.curfont
        font.pointSize: 13
        onLinkActivated: Qt.openUrlExternally(link)
        MouseArea {
            id: m2
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
            onEntered: m2.cursorShape = Qt.PointingHandCursor
            onExited: m2.cursorShape = Qt.ArrowCursor
        }
    }
}
