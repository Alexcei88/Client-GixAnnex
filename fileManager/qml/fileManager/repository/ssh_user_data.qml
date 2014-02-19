import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
Rectangle {

    // функция перехода на следующую страницу
    function nextPage()
    {
        console.log("Page \"ssh_user_data\": call next page...");
        var nextpage = modelRepoXMLCloud.get(stackView.selectIndexRepository).url2;
        console.log(nextpage);
        if(nextpage !== "")
            stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true})
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

        property int baseHeight: 25
        property int widthFieldOption: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: head.bottom
        anchors.topMargin: 15
        height: 5 * baseHeight +  column.spacing * 4
        spacing: 10
        PropertyInputValue {
            nameOption: "Host name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
        }
        PropertyInputValue {
            nameOption: "User name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            focus: true
        }
        PropertyInputValue {
            nameOption: "Source URL:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight

        }
        PropertyInputValue {
            nameOption: "Name repository:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
        }
        PropertyInputValue {
            nameOption: "Port:"
            widthFieldOption: column.widthFieldOption
            valueOption: "22"
            height: column.baseHeight

        }
    }

}
