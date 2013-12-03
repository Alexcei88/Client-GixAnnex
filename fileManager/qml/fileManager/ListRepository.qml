import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
import Repository 1.0

Rectangle {

    // ФУНКЦИИ, СВО-ВА И СИГНАЛЫ
    //-------------------------------------------------------------------------/

    property int widthRepoSync: 0
//    property int : value
    // сигнал о выборе нового репозитория
    signal selectNewRepository(string path)

    function reloadModel()
    {
        modelRepoXML.reload();
    }

    //-------------------------------------------------------------------------/

    ControllerRepository {
        id: repository
    }
    XmlListModel{
        id: modelRepoXML
        source: "../../ganx-repository.xml"
        query: "/reporegistry/repo"

        XmlRole { name: "localPath"; query: "@localUrl/string()" }
        XmlRole { name: "nameRepo"; query: "@nameRepo/string()" }
    }

    SystemPalette { id: sysPal }


    GridView
    {
        id: viewModel
        model: modelRepoXML

        width: parent.width

        cellHeight: 32
        cellWidth: parent.width

        currentIndex: 0
        anchors.fill: parent

        keyNavigationWraps: true
        delegate:
            Item
            {
                id: viewItem
                height: viewModel.cellHeight
                width: viewModel.cellWidth

                onWidthChanged:
                {
                    rowLayout = viewModel.cellWidth
                    itemText.width = width - widthRepoSync
                    textNameRepo.width = itemText.width - textNameRepo.anchors.leftMargin - 7
                }

                RowLayout
                {
                    id: rowLayout
                    anchors.fill: parent
                    width: parent.width

                    Image{
                        id: repoSync
                        anchors.leftMargin: 5
                        source: "qrc:/repo_on.png"
                        state: "SYNCING"
                        Component.onCompleted: {
                            widthRepoSync = width
                            itemText.width = viewItem.width - width
                            textNameRepo.width = itemText.width - 4 - 7
                        }
                    }

                    Item{
                        id: itemText
                        width: parent.width - repoSync.width
                        Text
                        {
                            id: textNameRepo
                            text: nameRepo
                            elide: Text.ElideRight
                            maximumLineCount: 1
                            renderType: Text.NativeRendering
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            width: parent.width -  anchors.leftMargin
                        }
                    }
                }
                // различные состояния, в которых может находиться репозиторий
                states:[
                        // 1. Идет синхронизация
                        State {
                            name: "SYNCING"
                            when: { repository.GetStateRepository(localPath) === "Syncing";}
                            PropertyChanges {
                                target: repoSync
                                source: "qrc:/repo_on.png"
                            }
                        },

                        // 2. Репозиторий сихронизирован
                        State {
                            name: "SYNCED"
                            when: { repository.GetStateRepository(localPath) === "Synced";}
                            PropertyChanges {
                                target: repoSync
                                source: "qrc:/repo_on.png"
                            }
                        },

                        // 3. Репозиторий выключен
                        State {
                            name: "DISABLE SYNC"
                            when: { repository.GetStateRepository(localPath) === "Disable_sincing";}
                            PropertyChanges {
                                target: repoSync
                                source: "qrc:/images/clear.png"

                            }
                        }
                        // папка с автосинхронизацией контента(посмотреть, это будет отдельным состоянием, или просто как)
                    ]

                MouseArea{
                    id: mouseAreaItem
                    anchors.fill: parent
                    onClicked: {
                        viewModel.currentIndex = model.index
                        selectNewRepository(localPath)
                    }
                }
            }
        highlight:
        Item {
            anchors.left: parent.left
            anchors.leftMargin: widthRepoSync
            width: parent.width
            Rectangle {
                color: sysPal.highlight
                radius: 1
                width: parent.width - widthRepoSync
                height: viewModel.cellHeight
            }
        }
        highlightMoveDuration: 0           

        Component.onCompleted:
        {
            if(GridView.isCurrentItem)
                selectNewRepository(localPath)
        }
    }
}
