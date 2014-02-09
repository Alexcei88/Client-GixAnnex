import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1
import Preferences 1.0

Rectangle {
    width: 200
    height: 100

    SystemPalette { id: sysPal }

    PreferencesApp
    {
        id: contrPreferences
    }

    color: sysPal.window
    Column {
        TabView
        {
            id: tabPreferences
            tabsVisible: true
            Component.onCompleted:
            {
                tabPreferences.addTab("General", generalPreferencesTab);
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

    Component {
        id: generalPreferencesTab

        Item {
            ColumnLayout {
                CheckBox {

                }

            }
        }
    }
}
