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
        var errorMessage = {val:1,toString:function(){return this.val}};
        if(checkInput(errorMessage))
        {
            console.log("Page \"saver_repository data\": call next page...");
            var nextpage = modelRepoXMLCommon.get(0).url_review;
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
        buttonNext.text = "Next >"

        var key = destUrl.nameOption.substring(0, destUrl.nameOption.length - 1);
        var value = addRepository.getOptions(key);
        destUrl.valueOption = value;

        key = nameRepository.nameOption.substring(0, nameRepository.nameOption.length - 1);
        value = addRepository.getOptions(key);
        nameRepository.valueOption = value;
    }

    function checkInput(errorMessage)
    {
        if(!checkForEmpty(destUrl, errorMessage))
            return false;

        if(!checkForEmpty(nameRepository, errorMessage))
            return false;

        return true;
    }

    function showErrorMessage(messageError)
    {
        rectForError.setSource("error_input_field.qml",
                               {"textError" : messageError.val }
                              );
    }

    FileDialog {
        id: fileDialogDestinition
        title: "Please choose a destinition folder"
        selectFolder: true
        onAccepted: {
            var path = fileDialogDestinition.folder.toString();
            if(path)
            {
                destUrl.valueOption = UtilsScript.getFullStrPath(path);
                if(destUrl.wasErrorValue)
                {
                    // убираем ошибку
                    rectForError.setSource("no_error_input_field.qml");
                    destUrl.wasErrorValue = false;
                }
            }
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

    Loader {
        id: rectForError
        anchors.top: head.bottom
        width: destUrl.width - anchors.leftMargin
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
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
                readonly: true
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

            onValueOptionChanged:
            {
                if(nameRepository.wasErrorValue && nameRepository.valueOption !== "")
                {
                    // убираем ошибку
                    rectForError.setSource("no_error_input_field.qml");
                    nameRepository.wasErrorValue = false;
                }
            }
        }
    }
}
