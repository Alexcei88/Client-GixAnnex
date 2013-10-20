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
    }

    ControllerIcons {
        id: contrIcons
        currentPath: UtilsScript.GetFullStrPath(dirModel.folder.toString())
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
        repository.currentPathRepo = path;
        contrIcons.currentPath = path;
        dirModel.folder = path;
        folderView.currentIndex = -1;
    }

    // функция взятия пути до иконки в зависимости от mymetype файла
    function getResourceImage(fileName)
    {
        var currentPathRepo = UtilsScript.GetFullStrPath(dirModel.folder.toString());
        var path = currentPathRepo + fileName;
        return contrIcons.GetPathIconsFile(path);
    }

    // функция обновления списка состояния иконок
    function updateListStateFileSync(folder)
    {
        contrIcons.currentPath = UtilsScript.GetFullStrPath(folder.toString());
    }

    // функция обновления состояния иконок у текущего списка
    function updateIconsStateFileSync()
    {
        console.log("updateIconsStateFileSync");
        var folderTemp = dirModel.folder;
        dirModel.folder = "";
        dirModel.folder = folderTemp;
    }
    //-------------------------------------------------------------------------/

    ContextMenu
    {
        id: menudirectory
        onOpenDirectory: {
            if(dirModel.isFolder(dirModel.index) && view.currentItem)
            {
                var fileName = view.currentItem.curFileName;
                var folder = dirModel.folder == "file:///" ? dirModel.folder + fileName : dirModel.folder +"/" + fileName;
                updateListStateFileSync(folder);
                dirModel.folder = folder;
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
            updateIconsStateFileSync();
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
                        state: "SYNCING"
                    }

                    // различные состояния, в которых может находиться директория(или файл)
                    states:[
                            State {
                                // 1. Идет синхронизация
                                name: "SYNCING"
                                when: { contrIcons.stateIconsFileSync[curFileName] === "SyncingF" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"
                                }
                            },
                            // 2. Имеются только символичеcкие ссылки
                            State {
                                name: "SYMBOL_LINK"
                                when: { contrIcons.stateIconsFileSync[curFileName] === "SyncedF" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/synced.png"
                                }
                            },
                            // 3. Имеются символичеcкие ссылки, некоторые из них с контентом
                            State {
                                name: "SYMBOL_LINK_AND_SOME_CONTENT"
                                when: { contrIcons.stateIconsFileSync[curFileName] === "sincsng"  }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"

                                }
                            },

                            // 4. Символическая ссылка с контенктом
                            State {
                                when: { contrIcons.stateIconsFileSync[curFileName] === "sinsdng"  }
                                name: "SYMBOL_LINK_AND_CONTENT"
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"

                                }
                            },
                            // 5. Синхронизация выключена
                            State {
                                name: "DISABLE_SYNC"
                                when: { contrIcons.stateIconsFileSync[curFileName] === "sinssng"  }
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
                        var folder = dirModel.folder == "file:///" ? dirModel.folder + curFileName : dirModel.folder +"/" + curFileName;
                        updateListStateFileSync(folder);
                        dirModel.folder = folder
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
