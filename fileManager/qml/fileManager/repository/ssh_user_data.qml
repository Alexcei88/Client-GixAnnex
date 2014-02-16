import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
Rectangle {

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

        property int baseHeight: 15
        property int widthFieldOption: 100
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 15
        anchors.top: head.bottom
        height: 4 * baseHeight +  column.spacing * 3
        spacing: 25
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
            nameOption: "Destinition URL:"
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
