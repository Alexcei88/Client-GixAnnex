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
        console.log("Page \"saver_repository data\": call next page...");
        var nextpage = modelRepoXMLCloud.get(stackView.selectIndexRepository).url_review;
        console.log(nextpage);

        // сохраняем опции
        var key = destUrl.nameOption.substring(0, destUrl.nameOption.length - 1);
        var value = destUrl.valueOption;
        addRepository.setOptions(key, value);

        key = nameRepository.nameOption.substring(0, nameRepository.nameOption.length - 1);
        value = nameRepository.valueOption;
        addRepository.setOptions(key, value);

        if(nextpage !== "")
            stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true})
    }
    function actualizeButton()
    {
        buttonNext.text = "Next >"

        var key = destUrl.nameOption.substring(0, destUrl.nameOption.length - 1);
        var value = addRepository.getOptions(key);
        destUrl.valueOption = value;

        key = nameRepository.nameOption.substring(0, nameRepository.nameOption.length - 1);
        value = addRepository.getOptions(key);
        nameRepository.valueOption = value;
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

        property int baseHeight: 23
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
                anchors.verticalCenterOffset: -4

            }
        }

        PropertyInputValue {
            id: nameRepository
            nameOption: "Name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            focus: true
        }
    }
}
