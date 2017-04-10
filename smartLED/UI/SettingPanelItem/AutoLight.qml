import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    SLGroupBox {
        width: parent.width
        height: 170
        title: qsTr("AutoLightSetting")
        fontfamily: fontmanager.curfont
        content: Rectangle {
            SLCheckBox {
                id: check1
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 40
                fontfamily: fontmanager.curfont
                text: qsTr("AutoLight")
                checked: true
            }

            Text {
                id: t1
                enabled: !check1.checked
                color: t1.enabled?"black":"gray"
                anchors.top: check1.bottom
                anchors.topMargin: 18
                anchors.left: parent.left
                anchors.leftMargin: 45
                font.family: fontmanager.curfont
                text: qsTr("LightLevel:")
            }

            SLComboBox {
                id: comboBox1
                enabled: !check1.checked
                anchors.verticalCenter: t1.verticalCenter
                anchors.left: t1.right
                anchors.leftMargin: 25
                fontfamily: fontmanager.curfont
                model: ["Level0","Level1","Level2",
                    "Level3","Level4"]
            }

            SLFlatButton {
                text: qsTr("OK")
                width: 240
                height: 20
                fontfamily: fontmanager.curfont
                anchors.top: t1.bottom
                anchors.topMargin: 27
                anchors.left: parent.left
                anchors.leftMargin: 50
                onClicked: {
                    var ll = comboBox1.currentText == "Level0"? 0:
                                comboBox1.currentText == "Level1"? 1:
                                comboBox1.currentText == "Level2"? 2:
                                comboBox1.currentText == "Level3"? 3:4
                    sc.sndControlFrame(check1.checked, ll)
                }
            }
        }
    }
}
