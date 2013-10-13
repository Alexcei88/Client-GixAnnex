import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0
import Repository 1.0
import Icons 1.0
import "utils.js" as UtilsScript

Rectangle
{

    //-------------------------------------------------------------------------/
    // ПОЛЬЗОВАТЕЛЬСКИЕ КЛАССЫ MVC

    ControllerRepository {
        id: repository
        currentPathRepo: UtilsScript.GetFullStrPath(dirModel.folder.toString())
    }

    ControllerIcons {
        id: contrIcons

    }

    // СВО-ВА, ФУНКЦИИ И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    property var folderModel: dirModel
    property var folderView: view

    // сигнал, что нужно показать свойства у директории
    signal showPropertyFile(var currentName)

    // сигнал о смене родительской директории
    signal changeParentFolder(string path)
    onChangeParentFolder:
    {
        // меняем рабочую директорию у модели
        dirModel.folder = path;
        repository.currentPathRepo = path;
        folderView.currentIndex = -1;
    }
    function getResourceImage(fileName)
    {
        var currentPathRepo = UtilsScript.GetFullStrPath(dirModel.folder.toString());
        var path = currentPathRepo + fileName;
        return contrIcons.GetPathIconsFile(path);
    }

    //-------------------------------------------------------------------------/

    ContextMenu
    {
        id: menudirectory
        onOpenDirectory: {
            if(dirModel.isFolder(dirModel.index) && view.currentItem)
            {
                var fileName = view.currentItem.curFileName;
                dirModel.folder = dirModel.folder == "file:///" ? dirModel.folder + fileName : dirModel.folder +"/" + fileName;
                view.currentIndex = -1;
            }
        }
        onGetContentDirectory:
        {
            var fileName = view.currentItem.curFileName;
            var currentPathRepo = UtilsScript.GetFullStrPath(dirModel.folder.toString());
            var relativePath = UtilsScript.GetRelativeStrPath(repository.currentPathRepo.toString(), currentPathRepo);
            var addFile =  relativePath === "" ? fileName : relativePath + "/" + fileName;
            repository.GetContentDirectory(addFile);
        }
        onDropContentDirectory:
        {
            var fileName = view.currentItem.curFileName;
            var currentPathRepo = UtilsScript.GetFullStrPath(dirModel.folder.toString());
            var relativePath = UtilsScript.GetRelativeStrPath(repository.currentPathRepo.toString(), currentPathRepo);
            var addFile =  relativePath === "" ? fileName : relativePath + "/" + fileName;
            repository.DropContentDirectory(addFile);
        }
    }

    width: 100
    height: 62

    Keys.forwardTo: [view]
    focus: true

    FolderListModel
    {
        id: dirModel
        folder: repository.GetDefaultRepositoryPath()
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

//        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0
        focus: true

        delegate: Item
        {
            id: itemView

            property bool isCurrent: GridView.isCurrentItem
            property var curFileName: fileName
            property real maxLengthOneLine: 0.95 * view.cellWidth

            width: view.cellWidth
            height: view.cellHeight

            Column
            {
                spacing: 8
                width: view.cellWidth

                Image{

                    id: imgFolder
                    source: if(dirModel.isFolder(model.index)) {
                                "qrc:/icons/folder.png" }
                            else {
                                getResourceImage(curFileName);
                            }
                    anchors.horizontalCenter: parent.horizontalCenter
                    Image{
                        id: dirSync
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.leftMargin: 2
                        source: "qrc:/synced.png"
                        state: "SYMBOL_LINK"
                    }

                    // различные состояния, в которых может находиться директория(или файл)
                    states:[
                            State {
                                // 1. Идет синхронизация
                                name: "SYNCING"
                                when: { contrIcons.stateIconsFileSync[0] === "syncing" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/synced.png"
                                }
                            },
                            // 2. Имеются только символичеcкие ссылки
                            State {
                                name: "SYMBOL_LINK"
                                when: { contrIcons.stateIconsFileSync[0] === "synced" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/disable_sync.png"

                                }
                            },
                            // 3. Имеются символичеcкие ссылки, некоторые из них с контентом
                            State {
                                name: "SYMBOL_LINK_AND_SOME_CONTENT"
                                when: { contrIcons.stateIconsFileSync[0] === "sincsng"  }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"

                                }
                            },

                            // 4. Символическая ссылка с контенктом
                            State {
                                when: { contrIcons.stateIconsFileSync[0] === "sinsdng"  }
                                name: "SYMBOL_LINK_AND_CONTENT"
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"

                                }
                            },
                            // 5. Синхронизация выключена
                            State {
                                name: "DISABLE_SYNC"
                                when: { contrIcons.stateIconsFileSync[0] === "sinssng"  }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/synced.png"

                                }
                            }

                            // папка с автосинхронизацией контента(посмотреть, это будет отдельным состоянием, или просто как)
                        ]
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
                    if(mouse.button === Qt.RightButton)
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
        }
    }
}
