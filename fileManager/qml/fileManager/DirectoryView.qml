import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0
import "utils.js" as UtilsScript

Rectangle
{
    property var folderModel: dirModel
    property var folderView: view

    // сигнал, что нужно показать свойства у директории
    signal showPropertyFile(var currentName)

    ContextMenu{
        id: menudirectory
        onOpenDirectory: {
            if(dirModel.isFolder(dirModel.index) && view.currentItem)
            {
                var fileName = view.currentItem.curFileName;
                dirModel.folder = dirModel.folder == "file:///" ? dirModel.folder + fileName : dirModel.folder +"/" + fileName;
                view.currentIndex = -1;
            }
        }

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
        showOnlyReadable: true
    }

    GridView
    {
        id: view
        model: dirModel
        width: parent.width

        anchors.fill: parent
        anchors.margins: 20
        currentIndex: -1

        cellHeight: 70
        cellWidth: 70

        keyNavigationWraps: true
        highlight: Rectangle {
            color: "skyblue"
            radius: 5
            z: 50
            anchors.margins: 20
        }

        highlightFollowsCurrentItem: true
        highlightMoveDuration: 1
        focus: true

        delegate: Item
        {
            id: itemView

            property var isCurrent: GridView.isCurrentItem
            property var curFileName: fileName
            property var maxLengthOneLine: 0.95 * view.cellWidth

            width: view.cellWidth
            height: view.cellHeight

            Column
            {
                spacing: 8
                width: view.cellWidth

                Image{
                    id: imgFolder
                    source: "qrc:/folder";
                    anchors.horizontalCenter: parent.horizontalCenter

                    Image{
                        id: dirSync
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        source: "qrc:/images/ok.png"
                    }
                }

                Text
                {
                    id: nameFolder
                    renderType: Text.NativeRendering
                    text: curFileName
                    maximumLineCount: 1
                    elide: Text.ElideRight
                    anchors.horizontalCenter: imgFolder.horizontalCenter
                    Component.onCompleted:
                    {
                        var contentWidth = nameFolder.contentWidth;
                        var widthComp = contentWidth > itemView.maxLengthOneLine ? itemView.maxLengthOneLine : contentWidth;
                        nameFolder.width = widthComp;
//                        if(UtilsScript.lengthStr(curFileName, 500) > 10 )
//                        {
//                            console.log("length > 50");
//                            return;
//                        }
                    }
                }
            }
            MouseArea
            {
                id: contextMenu
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                hoverEnabled: true

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
                onEntered: {
                    // посылаем сигнал, что необходимо вывести свойства объекта, на который навели
                    showPropertyFile(curFileName)
                }
            }
            // различные состояния, в которых может находиться директория
            states:[
                    State {
                        // 1. Идет синхронизация
                        name: "SYNCING"
//                        PropertyChanges { target: menuBar; y: 0 }
//                        PropertyChanges { target: textArea; y: partition + drawer.height }
//                        PropertyChanges { target: drawer; y: partition }
//                        PropertyChanges { target: arrowIcon; rotation: 180 }
                    },
                    // 2. Имеются только символичеcкие ссылки
                    State {
                        name: "SYMBOL_LINK"
//                        PropertyChanges { target: menuBar; y: -height; }
//                        PropertyChanges { target: textArea; y: drawer.height; height: screen.height - drawer.height }
//                        PropertyChanges { target: drawer; y: 0 }
//                        PropertyChanges { target: arrowIcon; rotation: 0 }
                    },

                    // 3. Имеются символичеcкие ссылки, некоторые из них с контентом
                    State {
                        name: "SYMBOL_LINK_AND_SOME_CONTENT"
    //                        PropertyChanges { target: menuBar; y: -height; }
    //                        PropertyChanges { target: textArea; y: drawer.height; height: screen.height - drawer.height }
    //                        PropertyChanges { target: drawer; y: 0 }
    //                        PropertyChanges { target: arrowIcon; rotation: 0 }
                    },

                    // 4. Символическая ссылка с контенктом
                    State {
                        name: "SYMBOL_LINK_AND_CONTENT"
                    }

                    // папка с автосинхронизацией контента(посмотреть, это будет отдельным состоянием, или просто как)
                ]
        }
    }
}
