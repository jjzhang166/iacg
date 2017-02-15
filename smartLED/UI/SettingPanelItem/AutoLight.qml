import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Item {
    implicitWidth: 525
    implicitHeight: 430

    Connections {
        target: maildata
        onCollData: console.log("AutoLight:recv sig")
    }

    SLGroupBox {
        width: parent.width
        height: 170
        title: qsTr("AutoLightSetting")
        content: Rectangle {
            SLCheckBox {
                id: check1
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 40
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
                text: qsTr("LightLevel:")
            }

            SLComboBox {
                id: comboBox1
                enabled: !check1.checked
                anchors.verticalCenter: t1.verticalCenter
                anchors.left: t1.right
                anchors.leftMargin: 25
                model: ["Level0","Level1","Level2",
                    "Level3","Level4"]
            }

            SLFlatButton {
                text: qsTr("OK")
                width: 240
                height: 20
                anchors.top: t1.bottom
                anchors.topMargin: 27
                anchors.left: parent.left
                anchors.leftMargin: 50
                onClicked: {
                    var byte1 = "ff"
                    var byte2 = check1.checked? "01":"00"
                    var byte3 = comboBox1.currentText == "Level0"? "00":
                                comboBox1.currentText == "Level1"? "0a":
                                comboBox1.currentText == "Level2"? "14":
                                comboBox1.currentText == "Level3"? "1e":"28"
                    sc.writeByte(byte1+byte2+byte3)
                }
            }
        }
    }
}
