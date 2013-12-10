import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0
import Repository 1.0
import Icons 1.0
import FolderListModel 1.0
import Message 1.0

import "utils.js" as UtilsScript

FocusScope{
    //-------------------------------------------------------------------------/
    // ПОЛЬЗОВАТЕЛЬСКИЕ КЛАССЫ MVC

    ControllerRepository {
        id: repository
    }

    ControllerIcons {
        id: contrIcons
    }

    MessageBox{
        id: message
    }

    // СВО-ВА, ФУНКЦИИ И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    property alias folderModel: dirModel
    property alias folderView: view
    // сигнал, что нужно показать свойства у директории
    signal showPropertyFile(var currentName)

    //------------------------------------------------------------------------/
    // сигнал о смене родительской директории
    signal changeRepository(string path)
    onChangeRepository:
    {
        // меняем рабочую директорию у модели
        repository.currentPathRepo = path;
        changeParentFolder(path)
        dirModel.folder = path;
        folderView.currentIndex = -1;
        dirModel.lastIndex = -1;
        showPropertyFile("/")
    }
    //------------------------------------------------------------------------/
    // функция взятия пути до иконки в зависимости от mymetype файла
    function getResourceImage(fileName)
    {
        var path = dirModel.folder.toString() + "/" + fileName;
        return contrIcons.getPathIconsFileDirectoryView(path);
    }
    //------------------------------------------------------------------------/
    // функция смены отображаемой директории в классе ControllertIcons
    // (currentPath должна поменяться до того, как установиться новый folder у модели)
    function changeParentFolder(path)
    {
        contrIcons.currentPath = path
    }
    //------------------------------------------------------------------------/
    // функция обновления состояния иконок у текущего списка
    function updateIconsStateFileSync()
    {
        dirModel.updateModel();
        if(dirModel.lastIndex < dirModel.count)
        {
            view.currentIndex = dirModel.lastIndex;
        }
    }
    //------------------------------------------------------------------------/
    // функция проверки нахождения свойства folder впределах корневого пути репозитория
    // чтобы выше корня репозитория не выходить
    function isSubRootRepositoryDirectory(path)
    {
        return repository.dirIsSubRootDirRepository(path)
    }

    //-------------------------------------------------------------------------/

    SystemPalette { id: sysPal }

    ContextMenu
    {
        id: menudirectory
        onOpenDirectory: {
            if(dirModel.isFolder(dirModel.index) && view.currentItem)
            {
                var fileName = view.currentItem.curFileName;
                var folder = dirModel.folder == "file:///" ? dirModel.folder + fileName : dirModel.folder +"/" + fileName;
                changeParentFolder(folder)
                dirModel.folder = folder;
                dirModel.lastIndex = -1;
                view.currentIndex = -1;
            }
        }
        onGetContentDirectory:
        {
            if(view.currentItem)
                repository.getContentDirectory(view.currentItem.curFileName);
        }
        onDropContentDirectory:
        {
            if(view.currentItem)
                repository.dropContentDirectory(view.currentItem.curFileName);
        }
        onRemoveDirectory:
        {
            if(view.currentItem)
            {
                var fileName = view.currentItem.curFileName;
                var text = "Do you really want to delete <i>" + fileName + "</i>?<br>";
                if(message.showConfirmMessage("Warning", text))
                    repository.removeDirectory(fileName);
            }
        }
    }

    id: focusScope
    width: 100
    height: 62

    BorderImage {
        anchors.fill: parent
        source: Settings.style + "/../Base/images/editbox.png"
        border { left: 4; top: 4; right: 4; bottom: 4 }
        BorderImage {
            anchors.fill: parent
            anchors.margins: -1
            anchors.topMargin: -2
            anchors.rightMargin: 0
            anchors.bottomMargin: 1
            source: Settings.style + "/../Base/images/focusframe.png"
            visible: focusScope.activeFocus ? true : false
            border { left: 4; top: 4; right: 4; bottom: 4 }
        }
    }

    NewFolderListModel
    {
        property int lastIndex: -1

        id: dirModel
        folder: repository.getDefaultRepositoryPath()
        showDirs: true
        showDirsFirst: true
        showOnlyReadable: false
        sortField: NewFolderListModel.Type

        Component.onCompleted: {
            contrIcons.currentPath = folder
        }

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
        highlight:
            Rectangle
            {
                color: sysPal.highlight
                radius: 5
                z: 50
                anchors.margins: 20
            }

        Component.onCompleted:
        {
            // запускаем поток обновления состояния иконок
            contrIcons.startThreadIconsSync();
            showPropertyFile("/")
        }

        highlightMoveDuration: 0
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            // разрешаем распостраняться сигналу по иерархии вверх
            propagateComposedEvents: true
            onClicked: {
                focusScope.focus = true;
                // сигнал до конца не обработали, прокидываем по иерархии дальше
                mouse.accepted = false;

            }
        }
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
                    source: getResourceImage(curFileName);
                    anchors.horizontalCenter: parent.horizontalCenter
                    Image
                    {
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
                                when: { contrIcons.stateIconsFileSyncQML[curFileName] === "SyncingF" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/syncing.png"
                                }
                            },
                            // 2. Синхронизация завершилась
                            State {
                                name: "SYNCED"
                                when: { contrIcons.stateIconsFileSyncQML[curFileName] === "SyncedF" }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/synced.png"
                                }
                            },
                            // 3. Синхронизация завершилась неудачно
                            State {
                                name: "SYNCED_ERROR"
                                when: { contrIcons.stateIconsFileSyncQML[curFileName] === "SyncedFError"  }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/disable_sync.png"
                                }
                            },

                            // 4. Синхронизация выключена
                            State {
                                name: "DISABLE_SYNC"
                                when: { contrIcons.stateIconsFileSyncQML[curFileName] === "sinssng"  }
                                PropertyChanges {
                                    target: dirSync
                                    source: "qrc:/synced.png"

                                }
                            }
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
                    view.currentIndex = model.index;
                    dirModel.lastIndex = model.index;
                    if(mouse.button === Qt.RightButton)
                    {
                        menudirectory.popup()
                        focusScope.focus = true
                    }
                }
                onDoubleClicked:
                {
                    if(dirModel.isFolder(model.index))
                    {
                        var folder = dirModel.folder == "file:///" ? dirModel.folder + curFileName : dirModel.folder +"/" + curFileName;
                        changeParentFolder(folder)
                        dirModel.folder = folder
                        dirModel.lastIndex = -1;
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
