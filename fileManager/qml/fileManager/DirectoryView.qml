import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0

Rectangle
{
    ContextMenu{
        id: menudirectory
    }

    width: 100
    height: 62

    Keys.forwardTo: [view]
    focus: true

    // FolderListModel
    FolderListModel
    {
        id: dirModel
        folder: "/home"
    }

    GridView
    {
       id: view
       model: dirModel
       width: parent.width

       anchors.fill: parent
       anchors.margins: 20

       cellHeight: 40
       cellWidth: 50

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
           property var curModel: GridView.model

           width: view.cellWidth
           height: view.cellHeight

           Image{
               source: "qrc:/folder"; anchors.horizontalCenter: parent.horizontalCenter
           }

               Text
               {
                   anchors.centerIn: parent
                   renderType: Text.NativeRendering
                   text: "%1%2".arg(fileName).arg(isCurrent ? " *" : "")
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
                   onDoubleClicked: {/* открытие файла(или вход в директорию, и перерисовка всего*/

                                        dirModel.folder = dirModel.folder +"/"+fileName;
                                }

               }
           }
    }
}
