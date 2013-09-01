import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Rectangle
{

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

           focus: true
           Keys.onPressed: {
                   console.log("press Key");
                   if (event.key == Qt.Key_Left) {
                       console.log("move left");
                       event.accepted = true;
                       view.moveCurrentIndexLeft()
                   }
               }

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
                   anchors.fill: parent
                   onClicked: view.currentIndex = model.index
               }
           }
        }
    }

}
