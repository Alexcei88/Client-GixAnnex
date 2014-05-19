import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0

Rectangle
{
    id: mainRectangle
    width: 900
    height:570

    SystemPalette { id: sysPal }

    color: sysPal.window

    Column
    {
        id: mainColumn

        spacing: 1
        visible: parent.visible
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // сверху панелька
        RowLayout
        {
            id: rowToolBar
            width: parent.width
            ToolBar
            {
                id: toolBar
                property alias folderModel: windowContent.folderModel
                property alias folderView: windowContent.folderView
                implicitWidth: parent.width
                RowLayout
                {
                    ToolButton{
                        iconSource:"qrc:back"
                        onClicked: {
                            var folder = toolBar.folderModel.parentFolder;
                            // если итоговый путь будет подкорнем корня репозитория, то переходим назад
                            // иначе ничего не делаем
                            if(windowContent.isSubRootRepositoryDirectory(folder))
                            {
                                windowContent.changeParentFolder(folder)
                                toolBar.folderModel.folder = folder;
                                toolBar.folderModel.lastIndex = -1;
                                toolBar.folderView.currentIndex = -1;
                            }
                        }
                    }
                    ToolButton{
                        iconSource: "qrc:forward"
                        onClicked: {
                            // проверка, есть ли выделенная папка
                            if(toolBar.folderView.currentItem)
                            {
                                var fileName = toolBar.folderView.currentItem.curFileName;
                                var folder = toolBar.folderModel.folder == "file:///" ? toolBar.folderModel.folder + fileName : toolBar.folderModel.folder +"/" + fileName;;

                                windowContent.changeParentFolder(folder)
                                toolBar.folderModel.folder = folder;
                                toolBar.folderView.currentIndex = -1;
                                toolBar.folderModel.lastIndex = -1;
                            }
                        }
                    }
                    // фильтр вывода файлов(директории к сож нет)
                    FilterBox
                    {
                        id: filterDir
                        onFilterChanges: {
                            toolBar.folderModel.nameFilters = textFilter.toString() + "*";
                            toolBar.folderView.currentIndex = -1;
                            toolBar.folderModel.lastIndex = -1;
                            toolBar.folderView.update();
                        }
                    }

                    ToolButton{
                        text: "аав1"
                    }
                }               
            }
        }

        WindowContent
        {
            visible: parent.visible
            // здесь будет отображаться контент
            id: windowContent
            width: parent.width
            height: parent.height - toolBar.height - statusBar.height - 2 * parent.spacing
            focus: true
        }

        StatusBar
        {
            visible: parent.visible
            id: statusBar
            width: parent.width
            RowLayout
            {
                width: parent.width
                Label {
                    width: parent.width
                    text: "Read OnlyRead"
                }
            }
        }
    }
}
