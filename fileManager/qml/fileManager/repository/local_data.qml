import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import "../utils.js" as UtilsScript

import "../propertyFile"

Rectangle {

    function nextPage()
    {
        if(checkInput())
        {
            // сохраняем опции
            var key = sourceUrl.nameOption.substring(0, sourceUrl.nameOption.length - 1);
            var value = sourceUrl.valueOption;
            addRepository.setOptions(key, value);

            console.log("Page \"ssh_user_data\": call next page...");
            var nextpage = modelRepoXMLCommon.get(0).url_save;
            console.log(nextpage);
            if(nextpage !== "")
                stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true})
        }
    }
    function actualizeButton()
    {
        var key = sourceUrl.nameOption.substring(0, sourceUrl.nameOption.length - 1);
        var value = addRepository.getOptions(key);
        sourceUrl.valueOption = value;

    }

    function checkInput()
    {
        if(!checkForEmpty(sourceUrl))
            return false;
        return true;
    }

    SystemPalette { id: sysPal }
    color: sysPal.window

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

    FileDialog {
        id: fileDialogSource
        title: "Please choose a source folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogSource.folder.toString();
            sourceUrl.valueOption = UtilsScript.getFullStrPath(path);
        }
        onRejected: {
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
        height: baseHeight
        spacing: 10

        Row {
            anchors.right: parent.right
            anchors.left: parent.left
            height: column.baseHeight
            spacing: 25
            PropertyInputValue {
                id: sourceUrl
                nameOption: "Source URL:"
                widthFieldOption: column.widthFieldOption
                height: column.baseHeight
            }
            Button {
                id: buttonDestBrowser
                text: "Browser"
                onClicked:  {
                    fileDialogSource.open();
                }
                anchors.verticalCenter: sourceUrl.verticalCenter
                anchors.verticalCenterOffset: -4

            }
        }
    }
}
