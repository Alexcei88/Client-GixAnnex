import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 1.0
// окно с отображением контента

Rectangle
{
    id: mainRectangle
    width: 900
    height:570

    Column
    {
        Keys.forwardTo: [windowContent]

        spacing: 5
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        // сверху панелька
        RowLayout{
            ToolBar
            {
                id: toolBar
                property var folderModel: windowContent.folderModel
                property var folderView: windowContent.folderView

                RowLayout{
                    width: parent.width
                    ToolButton{
                        iconSource:"qrc:back"
                        onClicked: {
                            console.log("Back folder");
                            toolBar.folderModel.folder = toolBar.folderModel.parentFolder;
                            toolBar.folderView.currentIndex = -1;
                        }
                    }
                    ToolButton{
                        iconSource: "qrc:forward"
                        onClicked: {
                            console.log("Forward folder");
                            var fileName = toolBar.folderView.currentItem.curFileName;
                            toolBar.folderModel.folder = toolBar.folderModel.folder == "file:///" ? toolBar.folderModel.folder + fileName : toolBar.folderModel.folder +"/" + fileName;
                            toolBar.folderView.currentIndex = -1;
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
            // здесь будет отображаться контент
            id: windowContent
            width: parent.width
            height: parent.height - toolBar.height - statusBar.height - 2 * parent.spacing
            focus: true
        }

        StatusBar
        {

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
