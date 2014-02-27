import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "../propertyFile"

Rectangle {


    function nextPage()
    {

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

        id: column

        property int baseHeight: 23
        property int sizeFont: 14
        property int widthFieldOption: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: head.bottom
        anchors.topMargin: 15
        height: 4 * baseHeight +  column.spacing * 3
        spacing: 10
        PropertyValue {
            nameOption: "Host name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
        PropertyValue {
            nameOption: "User name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            focus: true
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
        PropertyValue {
            nameOption: "Directory:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
        PropertyValue {
            nameOption: "Port:"
            widthFieldOption: column.widthFieldOption
            valueOption: "22"
            height: column.baseHeight
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
        PropertyValue {
            nameOption: "Destinition URL:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
        PropertyValue {
            nameOption: "Name:"
            widthFieldOption: column.widthFieldOption
            height: column.baseHeight
            sizeFont: column.sizeFont
            anchors.left: column.left
        }
}

}
