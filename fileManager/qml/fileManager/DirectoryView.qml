import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0

Rectangle
{
    property var folderModel: dirModel
    property var folderView: view

    ContextMenu{
        id: menudirectory
    }

    width: 100
    height: 62

    Keys.forwardTo: [view]
    focus: true

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

       cellHeight: 70
       cellWidth: 70

//       keyNavigationWraps: true
       highlight: Rectangle {
                   color: "skyblue"
                   radius: 5
                   z: 50                  
               }

       highlightFollowsCurrentItem: true
       highlightMoveDuration: 1
       focus: true

       delegate: Item
       {
           property var isCurrent: GridView.isCurrentItem

           width: view.cellWidth
           height: view.cellHeight

           Column
           {
               spacing: 8
               Image{
                   source: "qrc:/folder"; /*anchors.horizontalCenter: parent.horizontalCenter*/
               }

               Text
               {
                   renderType: Text.NativeRendering
                   text: "%1%2".arg(fileName).arg(isCurrent ? " *" : "")
               }
           }
           MouseArea
           {
               id: contextMenu
               anchors.fill: parent
               acceptedButtons: Qt.LeftButton | Qt.RightButton
               onClicked:
               {
                   view.currentIndex = model.index
                   if(mouse.button == Qt.RightButton)
                       menudirectory.popup()
                }
               onDoubleClicked:
               {// открытие файла(или вход в директорию, и перерисовка всего
                   if(dirModel.isFolder(model.index))
                   {
                       dirModel.folder = dirModel.folder == "/" ? dirModel.folder + fileName : dirModel.folder +"/" + fileName;
                       console.log(dirModel.folder);
                       view.currentIndex = model.index;
                   }
               }

           }
        }
    }
}
