import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0
// окно с отображением контента
import "getContent"
Rectangle
{
    id: mainRectangle
    width: 900
    height:570

    signal updateModel();

    function reloadModel()
    {
        console.log("dgfgfs");
    }

    Column
    {
        Keys.forwardTo: [windowContent, toolBar]

        spacing: 1
        visible: parent.visible
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // сверху панелька
        RowLayout
        {
            ToolBar
            {
                id: toolBar
                property var folderModel: windowContent.folderModel
                property var folderView: windowContent.folderView

                RowLayout
                {
                    width: parent.width
                    ToolButton{
                        iconSource:"qrc:back"
                        onClicked: {
                            toolBar.folderModel.folder = toolBar.folderModel.parentFolder;
                            toolBar.folderView.currentIndex = -1;
                        }
                    }
                    ToolButton{
                        iconSource: "qrc:forward"
                        onClicked: {
                            // проверка, есть ли выделенная папка
                            if(toolBar.folderView.currentItem)
                            {
                                var fileName = toolBar.folderView.currentItem.curFileName;
                                toolBar.folderModel.folder = toolBar.folderModel.folder == "file:///" ? toolBar.folderModel.folder + fileName : toolBar.folderModel.folder +"/" + fileName;
                                toolBar.folderView.currentIndex = -1;
                            }
                        }
                    }

                    ToolButton{
                        text: "аав1"
                    }
                }
            }
            // фильтр вывода файлов(директории к сож нет)
            FilterBox
            {
                id: filterDir;
                onFilterChanges: {
                    toolBar.folderModel.nameFilters = textFilter.toString() + "*";
                    toolBar.folderView.currentIndex = -1;
                    toolBar.folderView.update();
                }
            }
        }

        GetContent{
            width: 100
            height: 20
            visible: false
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
