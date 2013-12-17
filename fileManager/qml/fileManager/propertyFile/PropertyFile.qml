import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import Icons 1.0

Rectangle
{
    id: propertyRect

    //-------------------------------------------------------------------------/
    // ПОЛЬЗОВАТЕЛЬСКИЕ КЛАССЫ MVC

    ControllerIcons {
        id: repositoryIcons
    }
    //-------------------------------------------------------------------------/

    // СВО-ВА, СИГНАЛЫ, МЕТОДЫ
    //-------------------------------------------------------------------------/
    property var folderView: null
    property string lastFileName: ""

    // сигнал, которые говорит, что нужно обновить данные о свойствах папки(файла)
    signal updateData(var fullPath, var currentName)
    onUpdateData:
    {
        if(folderView) // проверка, инициализировали ли представление
        {
            if(lastFileName === currentName)
                // у данного файла уже выведены параметр на экран, еще раз не выводим
                return;

            name.text = currentName;
            lastFileName = currentName;
            propertyLastModified.valueOption = repositoryIcons.getLastModifiedFile(fullPath);
            propertySize.valueOption = repositoryIcons.getSizeFile(fullPath);
            iconsImage.source = repositoryIcons.getPathIconsFilePropertyFile(fullPath);
        }
    }

    width: parent.width
    height: parent.height

    onWidthChanged:
    {
        columnHead.width = width
        separatorRect.width = width - 30
    }

    ColumnLayout {
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        id: columnHead

        Image {
            id: iconsImage
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text
        {
            id: name
            text: "FileName"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        // разделитель(взят из ToolBarStyle)
        Rectangle {
            id: separatorRect
            width: parent.width - 30
            height: 1
            color: "#999"
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

    ColumnLayout
    {
        id:column
        spacing: 5

        property int maxWidthNameField: 74

        anchors.top: columnHead.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: columnHead.horizontalCenter
        anchors.horizontalCenterOffset: -maxWidthNameField

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
