import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import Repository 1.0
import "../utils.js" as UtilsScript
import Error 1.0

Rectangle
{
    ControllerRepository {
        id: repository
    }

    SystemPalette { id: sysPal }

    ErrorMessage{
        id: errorS
    }

    FileDialog {
        id: fileDialogSource
        title: "Please choose a source folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogSource.folder.toString();
            sourсeUrl.text = UtilsScript.getFullStrPath(path);
        }
        onRejected: {
        }
    }

    FileDialog {
        id: fileDialogDestinition
        title: "Please choose a destinition folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogDestinition.folder.toString();
            destUrl.text = UtilsScript.getFullStrPath(path);
        }
        onRejected: {
        }
    }

    id: rect
    x: 0
    y: 0
    width: 500
    color: sysPal.window
    height: columnOptionClone.height + buttonRow.height + 50

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
                text: "URL..."
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
                text: "URL"
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


            Text
            {
                id: nameRepo
                text:"Name: "
                width: columnOptionClone.widthText
            }

            TextField
            {
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
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    var result = repository.StartCloneRepository(destUrl.text, sourсeUrl.text, valueNameRepo.text);
                    var title = "Error Clone Repository"
                    if(result === 5)
                    {
                        // директории назначения не существует, выдавать ошибку клонирования
                        var text = "Destinition URL <i>" + destUrl.text +"</i> not exist.<br>";
                        var text1 = text + "Clone repository not execute!"
                        errorS.ShowErrorMessage(title, text1);
                    }
                    else if(result === 4)
                    {
                        // ошибка во время исполнения
                        var text = repository.GetLastError();
                        errorS.ShowErrorMessage(title, text);
                    }
                    else
                    {
                        // клонирование репозитория завершилось успешно
                    }

                }
            }
        }

        Button{
            id: cancelButton
            text: "Cancel"
            MouseArea{
                anchors.fill: parent
                onClicked:
                {
                    repository.CancelCloneRepository()
                }
            }
        }
    }

}

