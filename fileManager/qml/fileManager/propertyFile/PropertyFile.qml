import QtQuick 2.1
import QtQuick.Layouts 1.0

Rectangle
{
    id: propertyRect
    property var folderView: null

    // сигнал, которые говорит, что нужно обновить данные
    signal updateData(var currentName)

    // обработчик сигнала updateData
    onUpdateData:
    {
        if(folderView) // проверка, инициализировали ли представление
        {
            name.text = currentName;
            propertyWhereis.nameOption = "New Data";
        }
    }

//        BorderImage {
//            source: "qrc:images/lineedit_bg.png"
//            width: parent.width; height: parent.height
//            border { left: 4; top: 4; right: 4; bottom: 4 }
//        }

    width: parent.width
    height: parent.height

    border.color: "black"
    border.width: 1
    radius: 5
    Text
    {
        id: name
        text: "FileName"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout
    {
        id:column
        spacing: 5

        property int maxWidthNameField: 74

        //        onWidthChanged: {console.log(column.width) }
        anchors.top: name.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: name.horizontalCenter
        anchors.horizontalCenterOffset: -maxWidthNameField

        PropertyValue
        {
            id: propertyWhereis
            nameOption: "WhereIs: "
            valueOption: "here"
            widthFieldOption: column.maxWidthNameField
            height: 20
            //            onWidthChanged: {console.log(property1.width) }

        }

        PropertyValue
        {
            id: propertySize
            nameOption: "Size: "
            widthFieldOption: column.maxWidthNameField
            height: 20
        }

        PropertyValue
        {
            id: propertyLastModified
            nameOption: "LastModified: "
            widthFieldOption: column.maxWidthNameField
            height: 20
        }
    }

    TextEdit {
        id: text_edit1
        x: -28
        y: -103
        width: 80
        height: 20
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }

    PropertyValue {
        id: propertyvalue1
        x: 265
        y: -52
    }
}
