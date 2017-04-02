import QtQuick 2.0
import QtQuick.Controls 1.4
import SLComponent 1.0

Rectangle {
    id: rectangle1
    color: "white"
    width: 525
    height: 430
    ScrollView {
        id: sv
        anchors.fill: parent
        ListView {
            id: listView
            anchors.fill: parent
            cacheBuffer: 512
            delegate: Item {
                width: parent.width
                height: ref_height
                Loader {
                    id: eloader
                    anchors.fill: parent
                    source: com_source
                }
            }
            model: ListModel {

                ListElement {
                    com_source: "qrc:/UI/SettingPanelItem/MailSetting.qml"
                    ref_height: 235
                }

                ListElement {
                  com_source: "qrc:/UI/SettingPanelItem/FontSetting.qml"
                  ref_height: 100
                }

                ListElement {
                    com_source: "qrc:/UI/SettingPanelItem/AutoLight.qml"
                    ref_height: 170
                }

                ListElement {
                    com_source: "qrc:/UI/SettingPanelItem/TmpSetting.qml"
                    ref_height: 280
                }

                ListElement {
                    com_source: "qrc:/UI/SettingPanelItem/HumiSetting.qml"
                    ref_height: 280
                }

                ListElement {
                    com_source: "qrc:/UI/SettingPanelItem/ButtonPanel.qml"
                    ref_height: 70
                }
            }
        }
    }
}
