import QtQuick 2.1
import QtQuick.Layouts 1.0
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
    property string folderPath: ""

    // сигнал, которые говорит, что нужно обновить данные о свойствах папки(файла)
    signal updateData(var currentName)
    onUpdateData:
    {
        if(folderView) // проверка, инициализировали ли представление
        {
            name.text = currentName;
            propertyWhereis.nameOption = "New Data";
            propertyLastModified.valueOption = repositoryIcons.GetLastModifiedFile(currentName);
            propertySize.valueOption = repositoryIcons.GetSizeFile(currentName);
            iconsImage.source = getResourceImage(currentName)
        }
    }

    // функция взятия пути до иконки в зависимости от mymetype файла
    function getResourceImage(fileName)
    {
        var path = folderPath + "/"+fileName;
        return repositoryIcons.GetPathIconsFilePropertyFile(path);
    }
    //-------------------------------------------------------------------------/

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

    ColumnLayout {

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
            id: propertyWhereis
            nameOption: "WhereIs: "
            valueOption: "here"
            widthFieldOption: column.maxWidthNameField
            height: 20
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
