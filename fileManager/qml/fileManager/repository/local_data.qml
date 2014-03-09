import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import "../utils.js" as UtilsScript

import "../propertyFile"

Rectangle {

    function nextPage()
    {
        var errorMessage = {val:1,toString:function(){return this.val}};
        if(checkInput(errorMessage))
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
        else
        {
            showErrorMessage(errorMessage);
        }
    }

    function prevPage()
    {

    }

    function actualizeButton()
    {
        var key = sourceUrl.nameOption.substring(0, sourceUrl.nameOption.length - 1);
        var value = addRepository.getOptions(key);
        sourceUrl.valueOption = value;

    }

    function checkInput(errorMessage)
    {
        if(!checkForEmpty(sourceUrl, errorMessage))
            return false;
        return true;
    }

    function showErrorMessage(messageError)
    {
        rectForError.setSource("error_input_field.qml",
                               {"textError" : messageError.val }
                              );
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

    Loader {
        id: rectForError
        anchors.top: head.bottom
        width: sourceUrl.width - anchors.leftMargin
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }

    FileDialog {
        id: fileDialogSource
        title: "Please choose a source folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogSource.folder.toString();
            if(path)
            {
                sourceUrl.valueOption = UtilsScript.getFullStrPath(path);
                if(sourceUrl.wasErrorValue)
                {
                    // убираем ошибку
                    rectForError.setSource("no_error_input_field.qml");
                }
            }
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
        anchors.top: rectForError.bottom
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
                readonly: true
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
