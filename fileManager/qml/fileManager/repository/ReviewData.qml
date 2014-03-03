import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "../propertyFile"


Rectangle {

    default property alias content: columnPrederences.children
    property alias column: columnPrederences
    property int countOption: 4
    function nextPage()
    {
        console.log("Page \"ssh_review_data\": start clone...");
        var nextpage = modelRepoXMLCloud.get(stackView.selectIndexRepository).url_addrepo;
        console.log(nextpage);

        if(nextpage !== "")
            stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true})

        addRepository.startAddRepository();
    }

    function actualizeButton()
    {
        buttonNext.text = "Add"

        // заполняем поля, если они были заполнены
        for(var i = 0; i < column.children.length; ++i)
        {
            var key = column.children[i].nameOption.substring(0, column.children[i].nameOption.length - 1);
            var value = addRepository.getOptions(key);
            column.children[i].valueOption = value;
        }
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

        id: columnPrederences

        property int baseHeight: 23
        property int sizeFont: 14
        property int widthFieldOption: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: head.bottom
        anchors.topMargin: 15
        height: countOption * baseHeight +  column.spacing * (countOption - 1)
        spacing: 10
    }
}
