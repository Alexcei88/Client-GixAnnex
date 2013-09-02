import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Rectangle
{
    ContextMenu{
        id: menudirectory
    }

    width: 100
    height: 62

    Keys.forwardTo: [view]

    focus: true

    // модель, содержащая список текущих директорий
    ListModel
    {
       id: dirModel
       ListElement{ text: "Dir1"
                    color: "red"}
       ListElement{ text: "Dir2"
                    color: "white"}
       ListElement{ text: "Dir3"
                    color: "yellow"}

       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}
       ListElement{ text: "Dir3"
                    color: "yellow"}

    }

    GridView
    {
       id: view
       model: dirModel
       width: parent.width

       anchors.fill: parent
       anchors.margins: 20

       cellHeight: 80
       cellWidth: 80

//       keyNavigationWraps: true
       highlight: Rectangle {
                   color: "skyblue"
               }

       highlightFollowsCurrentItem: true
       highlightMoveDuration: 1
       focus: true
       enabled: true

       delegate: Item
       {
           property var view: GridView.view
           property var isCurrent: GridView.isCurrentItem

           width: view.cellWidth
           height: view.cellHeight

           Rectangle
           {

               anchors.margins: 5
               anchors.fill: parent
               color: model.color
               border {
                   color: "black"
                   width: 1

               }

               Text
               {
                   anchors.centerIn: parent
                   renderType: Text.NativeRendering
                   text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
               }

               MouseArea
               {
                   id: contextMenu
                   anchors.fill: parent
                   acceptedButtons: Qt.LeftButton | Qt.RightButton
                   onClicked: { view.currentIndex = model.index
                                if(mouse.button == Qt.RightButton)
                                    menudirectory.popup()
                                }

               }
           }
        }
    }

}
