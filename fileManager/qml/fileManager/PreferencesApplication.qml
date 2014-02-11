import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Preferences 1.0

Rectangle {

    SystemPalette { id: sysPal }

    PreferencesApp
    {
        id: contrPreferences
    }

    color: sysPal.window
    Column
    {
        id: column
        property int heightForButton: 0.04 * parent.height
        anchors.margins: 10

        spacing: 10
        anchors.fill: parent
        TabView
        {
            id: tabPreferences
            width: parent.width
            height: parent.height - column.heightForButton
                    - column.spacing - column.anchors.margins
            tabsVisible: true
            Component.onCompleted:
            {
                tabPreferences.addTab("General", generalPreferencesTab);
                tabPreferences.addTab("Repository", repositoryPreferencesTab);
            }
        }

        RowLayout {
            height: column.heightForButton
            width: parent.width
            Button
            {
                anchors.right: parent.right
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
    } // end column

    //-------------------------------------------------------------------------/
    // страницы TabView
    // general
    Component {
        id: generalPreferencesTab

        Item {
            anchors.fill: parent
            anchors.margins: 20
            Column{
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
            anchors.fill: parent
            anchors.margins: 20
            Rectangle
            {
                border.width: 2
                radius: 1
                GroupBox {
                    //anchors.fill: parent
                    title: qsTr("Mode")
                     ExclusiveGroup { id: group }
                       Row {
                           spacing: 2
                           RadioButton {
                               exclusiveGroup: group
                               checked: true
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
}
