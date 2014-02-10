import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1
import Preferences 1.0

Rectangle {
    width: 100
    height: 200

    SystemPalette { id: sysPal }

    PreferencesApp
    {
        id: contrPreferences
    }

    color: sysPal.window
    ColumnLayout {
        anchors.fill: parent
        TabView
        {
            id: tabPreferences
            tabsVisible: true
            Component.onCompleted:
            {
                tabPreferences.addTab("General", generalPreferencesTab);
                tabPreferences.addTab("Repository", repositoryPreferencesTab);
            }
        }

        RowLayout {
            Button
            {
                id: close
                text: qsTr("Close")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // закрыть форму
                        contrPreferences.closePreferencesAppView();
                    }
                }
            }
        }
    }
    // страницы TabView
    // general
    Component {
        id: generalPreferencesTab

        Item {
            anchors.margins: 40

            Column{
                height: parent.height
                anchors.fill: parent
                spacing: 10
                CheckBox {
                    text: qsTr("Show desktop notifications");
                }

                CheckBox {
                    text: qsTr("Start git-annex on system startup");
                }

            }
        }
    }
    // Repository
    Component {
        id: repositoryPreferencesTab

        Item {
            anchors.margins: 40
            GroupBox {
                title: qsTr("Mode")
                 ExclusiveGroup { id: group }
                   Row {
                       spacing: 2
                       RadioButton {
                           exclusiveGroup: group
                           text: qsTr("Direct")
                       }
                       RadioButton {
                           exclusiveGroup: group
                           text: qsTr("Indirect")
                       }
                   }
            }
        }
    }
}
