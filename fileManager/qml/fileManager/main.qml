import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

Rectangle
{
    width: 460
    height: 360

    ColumnLayout{

        spacing: 5
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        // сверху панелька

        ToolBar{
            id: toolBar
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            RowLayout{
                ToolButton{
                    text: "fff"
                }
                ToolButton{
                    text: "111"
                }
            }
        }

        Rectangle{
            anchors.top: toolBar.bottom
            height: 230
            width: parent.width
            //color: "#FF3001"
        }

        StatusBar{
            id: statusBar
            anchors.bottom: parent.bottom
            width: parent.width
        }
    }


}
