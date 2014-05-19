import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Preferences 1.0
import QtQuick.Dialogs 1.1

import "utils.js" as UtilsScript
import "secondary"

Window {

    id: window
    height: 400
    width: 400
    title: "Preferences repository"
    SystemPalette { id: sysPal }
    flags: Qt.Dialog
    modality: "ApplicationModal"
    visible: true

    PreferencesApp
    {
        id: contrPreferences
    }

    Rectangle {

        anchors.fill: parent
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
                    tabPreferences.addTab("Unknow", repositoryPreferencesTab);
                    tabPreferences.addTab("Advanced", advancedTab);
                }
            }

            RowLayout {
                height: column.heightForButton
                width: parent.width
                Button {
                    anchors.right: parent.right
                    id: close
                    text: qsTr("Close")
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            window.close();
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
                anchors.margins: 10

                ColumnLayout
                {
                    height: 120
                    width: parent.width
                    TextHead {
                        id: head
                        text: qsTr("Description repository")
                    }

                    TextArea {
                        id: descriptionRepository
                        text: ""
                        width: parent.width
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
        // Unknow
        Component {
            id: repositoryPreferencesTab

            Item {
                Component.onCompleted: {
                    var mode = repository.GetModeWorkRepositoryOfCurrentRepository()
                    if(mode === true)
                        direct.checked = true;
                    else
                        indirect.checked = true;
                }

                anchors.fill: parent
                anchors.margins: 20
                Rectangle
                {
                    border.width: 2
                    radius: 1
                    GroupBox {
                        title: qsTr("Mode")
                        ExclusiveGroup { id: group }
                        Row {
                            spacing: 2
                            RadioButton {
                                id: direct
                                exclusiveGroup: group
                                checked: true
                                text: qsTr("Direct")
                            }
                            RadioButton {
                                id: indirect
                                exclusiveGroup: group
                                text: qsTr("Indirect")
                            }
                        }
                    }
                }
            }
        }

        // Advanced
        Component {
            id: advancedTab

            Item {

                Component.onCompleted: {
                    destUrl.placeholderText = repository.getPathOfCurrentRepository();
                }
                FileDialog {
                    id: fileDialogDestinition
                    title: "Please choose a destinition folder"
                    selectFolder: true
                    onAccepted: {
                        var path = fileDialogDestinition.folder.toString();
                        destUrl.placeholderText = UtilsScript.getFullStrPath(path);
                        // начинаем перемещение
                        repository.movePathOfCurrentRepository(destUrl.placeholderText);
                    }
                    onRejected: {
                    }
                }
                anchors.fill: parent
                anchors.margins: 10

                Column {
                    anchors.fill: parent
                    spacing: 20

                    ColumnLayout {
                        width: parent.width
                        height: head.implicitHeight + buttonDestBrowser.implicitHeight
                        TextHead {
                            id: head
                            text: qsTr("Repository location")
                        }
                        RowLayout{
                            anchors.left: parent.left
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 15

                            TextField{
                                id: destUrl
                                Layout.fillWidth: true
                                focus: true
                                text: ""
                                readOnly: true
                            }

                            Button {
                                id: buttonDestBrowser
                                text: "Move"
                                onClicked:  {
                                    fileDialogDestinition.visible = true;
                                }
                            }
                        }
                    } // end ColumnLayout


                    // selective sync
                    ColumnLayout {
                        width: parent.width
                        height: head.implicitHeight + destUrl.implicitHeight
                        TextHead {
                            id: headSelective
                            text: qsTr("Selective auto get content")
                        }
                        RowLayout{
                            anchors.left: parent.left
                            anchors.horizontalCenter: parent.horizontalCenter
                            spacing: 15

                            Text{
                                id: text
                                height: 20
                                text: "Select which folders auto get content \nto this repository"
                                font {
                                    pixelSize: 12
                                }
                            }

                            Button {
                                id: buttonSelect
                                text: "Select"
                                Layout.fillWidth: true
                                onClicked:  {
                                    console.log("Здесь будет еще одно окно")
                                }
                            }
                        }
                    } // end ColumnLayout
                }

            }
        }
    } // end Rectangle
}
