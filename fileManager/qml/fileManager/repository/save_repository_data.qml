import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1

import "../utils.js" as UtilsScript

Rectangle {

    SystemPalette { id: sysPal }
    color: sysPal.window

    // функция перехода на следующую страницу
    function nextPage()
    {

    }

    FileDialog {
        id: fileDialogDestinition
        title: "Please choose a destinition folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogDestinition.folder.toString();
            destUrl.valueOption = UtilsScript.getFullStrPath(path);
        }
        onRejected: {
        }
    }

    Text {
        id: head
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 15

        text: "Adding a remote server using ssh"
        font {
            pixelSize: 16
            bold: true
        }
    }
    ColumnLayout {

        id: column

        property int baseHeight: 25
        property int widthFieldOption: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: head.bottom
        anchors.topMargin: 15
        height: 2 * baseHeight + column.spacing
        spacing: 10

        Row {
            anchors.right: parent.right
            anchors.left: parent.left
            height: column.baseHeight
            spacing: 25
            PropertyInputValue {
                id: destUrl
                nameOption: "Destinition URL:"
                widthFieldOption: column.widthFieldOption
                height: column.baseHeight
            }
            Button {
                id: buttonDestBrowser
                text: "Browser"
                onClicked:  {
                    fileDialogDestinition.open();
                }
                anchors.verticalCenter: destUrl.verticalCenter

            }
        }

        PropertyInputValue {
            nameOption: "Name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            focus: true
        }
    }
}
