import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0

Rectangle
{
    property var folderModel: dirModel
    property var folderView: view

    signal showPropertyFile(var currentName)

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
        showDirs: true
        showDirsFirst: true
    }

    GridView
    {

       id: view
       model: dirModel
       width: parent.width

       anchors.fill: parent
       anchors.margins: 20
       currentIndex: -1

       cellHeight: 80
       cellWidth: 70

       keyNavigationWraps: true
       highlight: Rectangle {
                   color: "skyblue"
                   radius: 5
                   z: 50
                   anchors.margins: 20
                   height: 30
                   width: 30
               }

       highlightFollowsCurrentItem: true
       highlightMoveDuration: 1
       focus: true

       delegate: Item
       {
           id: itemView

           property var isCurrent: GridView.isCurrentItem
           property var curFileName: fileName
           property var itemHover: null

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
                   text: "%1%2".arg(curFileName).arg(isCurrent ? "\*" : "")
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
               {
                   if(dirModel.isFolder(model.index))
                   {
                       dirModel.folder = dirModel.folder == "file:///" ? dirModel.folder + curFileName : dirModel.folder +"/" + curFileName;
                       console.log(dirModel.folder);
                       view.currentIndex = -1;

                   }
               }
               hoverEnabled: true
               onEntered: {
                    // посылаем сигнал, что необходимо вывести свойства
                   showPropertyFile(curFileName)
                   itemView.itemHover = this;
               }
           }
        }
    }
}
