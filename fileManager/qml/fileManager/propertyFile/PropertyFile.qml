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
    property var maximumWidth: propertyRect.Layout.maximumWidth
    property var minimumWidth: propertyRect.Layout.minimumWidth

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
        name.width = width - 40;
        if(width > maximumWidth - 1 || width < minimumWidth + 1)
            return;
        if(iconsImage.status === Image.Ready)
        {
//            columnHead.height += (columnHead.height * 0.008);
        }
    }

    ColumnLayout{
        width: parent.width
        id: columnHead
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: iconsImage
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Text {
        id: name
        text: "FileName"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : columnHead.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        width: parent.width - 40
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        font.bold: true
    }

    // разделитель(взят из ToolBarStyle)
    Rectangle {
        id: separatorRect
        width: parent.width - 30
        height: 1
        color: "#999"
        anchors.top: name.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout {
        id:column
        spacing: 5

        property int maxWidthNameField: 74

        anchors.top: separatorRect.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -maxWidthNameField

        PropertyValue
        {
            id: propertySize
            nameOption: "Size: "
            widthFieldOption: column.maxWidthNameField
            height: 10
        }

        PropertyValue
        {
            id: propertyLastModified
            nameOption: "LastModified: "
            widthFieldOption: column.maxWidthNameField
            height: 10
        }
    }
}
