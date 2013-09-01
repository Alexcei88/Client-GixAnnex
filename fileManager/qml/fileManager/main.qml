import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

// окно с отображением контента

Rectangle
{
    id: mainRectangle
    width: 900
    height:570

    Column{

        spacing: 5

        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        // сверху панелька

        ToolBar{
            id: toolBar
            width: parent.width

            RowLayout{
                width: parent.width
                ToolButton{
                    text: "fff"
                }
                ToolButton{
                    text: "111"
                }
                ToolButton{
                    text: "аав1"
                }

            }
        }

        WindowContent{
            // здесь будет отображаться контент

//            anchors.top: toolBar.bottom
//            anchors.bottom: statusBar.top
            width: parent.width
            height: parent.height - toolBar.height - statusBar.height - 2 * parent.spacing
            color: "white"
        }

        StatusBar{
            id: statusBar
            width: parent.width
            RowLayout {
                    width: parent.width
                    Label {
                        width: parent.width
                        text: "Read OnlyRead"}
                    }

        }
    }

}
