import QtQuick 2.1

Rectangle
{
    id: propertyRect

    width: parent.width
    height: parent.height

    // сигнал, которые говорит, что нужно обновить данные
    signal updateData()

    // обработчик сигнала updateData
    onUpdateData:
    {
        propertyWhereis.nameOption = "New Data";
    }

    //    BorderImage {
//        source: "qrc:images/lineedit_bg.png"
//        width: parent.width; height: parent.height
//        border { left: 4; top: 4; right: 4; bottom: 4 }
//    }
    border.color: "black"
    border.width: 1
    radius: 5
    Column
    {
        id:column
        width: 2.8 * parent.width/3
        spacing: 5
//        onWidthChanged: {console.log(column.width) }
        anchors.horizontalCenter: parent.horizontalCenter

        PropertyValue
        {
            id: propertyWhereis
            width: parent.width
            nameOption: "WhereIs: "
            valueOption: "here"
            height: 20
//            onWidthChanged: {console.log(property1.width) }

        }

        PropertyValue
        {
            id: propertySize
            nameOption: "Size: "
            width: parent.width
            height: 20
        }
    }
}
