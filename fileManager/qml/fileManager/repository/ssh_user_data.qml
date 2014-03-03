import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {

    // функция перехода на следующую страницу
    function nextPage()
    {
        if(checkInput())
        {
            // добавляем опции
            for(var i = 0; i < column.children.length; ++i)
            {
                var key = column.children[i].nameOption.substring(0, column.children[i].nameOption.length - 1);
                var value = column.children[i].valueOption;
                addRepository.setOptions(key, value);
            }

            console.log("Page \"ssh_user_data\": call next page...");
            var nextpage = modelRepoXMLCommon.get(0).url_save;
            console.log(nextpage);
            if(nextpage !== "")
                stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true})
        }
    }
    function actualizeButton()
    {
        // заполняем поля, если они были заполнены
        for(var i = 0; i < column.children.length; ++i)
        {
            var key = column.children[i].nameOption.substring(0, column.children[i].nameOption.length - 1);
            var value = addRepository.getOptions(key);
            column.children[i].valueOption = value;
        }
    }

    function checkInput()
    {
        if(!checkForEmpty(hostName))
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
        height: 4 * baseHeight +  column.spacing * 3
        spacing: 10
        PropertyInputValue {
            id: hostName
            nameOption: "Host name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
        }
        PropertyInputValue {
            id: userName
            nameOption: "User name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            focus: true
        }
        PropertyInputValue {
            id: directory
            nameOption: "Directory:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight

        }
        PropertyInputValue {
            id: port
            nameOption: "Port:"
            widthFieldOption: column.widthFieldOption
            valueOption: "22"
            height: column.baseHeight

        }
    }

}
