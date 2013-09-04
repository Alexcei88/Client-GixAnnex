import QtQuick 2.1

Rectangle {
    width: 100
    height: 62
//    BorderImage {
//        source: "qrc:images/lineedit_bg.png"
//        width: parent.width; height: parent.height
//        border { left: 4; top: 4; right: 4; bottom: 4 }
//    }
    border.color: "black"
    border.width: 1
    radius: 5
    Column{
    width: parent.width
    spacing: 10
    PropertyValue{
        width: parent.width
        height: 20
    }

    PropertyValue{
        width: parent.width
        height: 20
    }
    }
}
