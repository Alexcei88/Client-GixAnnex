import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import Repository 1.0
import "../utils.js" as UtilsScript

Rectangle
{
    ControllerRepository {
        id: repository
    }

    FileDialog {
        id: fileDialogSource
        title: "Please choose a source folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogSource.folder.toString();
            sourсeUrl.text = UtilsScript.GetFullStrPath(path);
        }
        onRejected: {
        }
    }

    FileDialog {
        id: fileDialogDestinition
        title: "Please choose a destinotion folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogDestinition.folder.toString();
            destUrl.text = UtilsScript.GetFullStrPath(path);
        }
        onRejected: {
        }
    }

    id: rect
    x: 0
    y: 0
    width: 500
    height: 62

    Column
    {
        id: columnOptionClone

        property int widthText: 110
        width: parent.width
        spacing: 10

        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter

        Row{
            id: rowSourceURL
            anchors.leftMargin: 10
            anchors.left: parent.left
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            spacing: 15

            Text{
                id: sourcePath
                text:"Source URL: "
                width: columnOptionClone.widthText
            }

            TextField{
                id: sourсeUrl
                implicitWidth: 300
                height: 20
                focus: true
                text: "cRedssssssffffffffffffffffffpo"
            }

            Button {
                id: buttonSourceBrowser
                text: "Browser"
                onClicked:  {
                    fileDialogSource.visible = true;
                }
            }
        }

        Row{
            anchors.leftMargin: 10
            anchors.left: parent.left
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            spacing: 15

            Text{
                id: destPath
                text:"Destinition URL: "
                width: columnOptionClone.widthText
            }

            TextField{
                id: destUrl
                implicitWidth: 300
                height: 20
                focus: true
                text: "home"
            }

            Button {
                id: buttonDestBrowser
                text: "Browser"
                onClicked:  {
                    fileDialogDestinition.visible = true;
                }

            }
        }

        Row{
            anchors.leftMargin: 10
            anchors.left: parent.left
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            spacing: 15


            Text{
                id: nameRepo
                text:"Name: "
                width: columnOptionClone.widthText
            }

            TextField{
                id: valueNameRepo
                implicitWidth: 300
                height: 20
                focus: true
                text: "Repo"
            }
        }
    } // end Column

    Row{

        id: buttonRow
        spacing: 20

        anchors.top: columnOptionClone.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: width/2 - 74
        width: parent.width

        Button{

            id: cloneButton
            text: "Clone"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    repository.StartCloneRepository(destUrl.text, sourсeUrl.text, valueNameRepo.text)
                }
            }
        }

        Button{
            id: cancelButton
            text: "Cancel"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    repository.CancelCloneRepository()
                }
            }
        }
    }

}

