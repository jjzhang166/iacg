import QtQuick 2.0
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 100
        title: qsTr("FontSetting")
        fontfamily: fontmanager.curfont
        content: Rectangle {
            Text {
                id: fonttext
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: familybox.left
                anchors.rightMargin: 30
                text: qsTr("Available Fonts:")
                font.family: fontmanager.curfont
            }

            SLComboBox {
                id: familybox
                enabled: !fontmanager.isListempty()
                width: 230
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 40
                fontfamily: fontmanager.curfont
                model: fontmanager.familylist
                onCurrentTextChanged:
                    fontmanager.curfont = currentText
            }
        }
    }
}
