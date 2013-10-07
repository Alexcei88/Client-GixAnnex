import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
import Repository 1.0

Rectangle {

    // ФУНКЦИИ, СВО-ВА И СИГНАЛЫ
    //-------------------------------------------------------------------------/
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
    width: 100
    height: 62
    border.width: 1
    border.color: "black"
    radius: 2

    XmlListModel{
        id: modelRepoXML
        source: "../../ganx-repository.xml"
        query: "/reporegistry/repo"

        XmlRole { name: "localPath"; query: "@localUrl/string()" }
        XmlRole { name: "nameRepo"; query: "@nameRepo/string()" }
    }

    GridView {
        id: viewModel
        model: modelRepoXML

        width: parent.width

        cellHeight: 15
        cellWidth: parent.width

        currentIndex: 0
        anchors.fill: parent

        keyNavigationWraps: true
        highlight: Rectangle {
            color: "skyblue"
            radius: 1
            anchors.margins: 20
        }
        /*Component.onCompleted:
        {
            changeParentFolder(viewModel.currentItem.localPath);
        }*/

        highlightMoveDuration: 0
        delegate:
            Item{
            id: viewItem
            height: viewModel.cellHeight
            width: viewModel.cellWidth

            Image{
                id: repoSync
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 5
                source: "qrc:/folder"
                state: "SYNCING"
            }
            Text{
                // anchors.horizontalCenter: parent.horizontalCenter
                text: nameRepo
            }
            MouseArea{
                id: mouseAreaItem
                anchors.fill: parent
                onClicked: {
                    viewModel.currentIndex = model.index
                    // посылаем сигнал о выборе нового репозитория
                    console.log(localPath)
                    selectNewRepository(localPath)
                }
            }
        }
    }
    // различные состояния, в которых может находиться репозиторий
    states:[
            // 1. Идет синхронизация
            State {
                name: "SYNCING"
//                        PropertyChanges { target: menuBar; y: 0 }
//                        PropertyChanges { target: textArea; y: partition + drawer.height }
//                        PropertyChanges { target: drawer; y: partition }
//                        PropertyChanges { target: arrowIcon; rotation: 180 }
                when: { var curState = repository.GetListRepository[0];
                            curState == "syncing"; }
                PropertyChanges {
                    target: repoSync
                    source: "qrc:/images/ok.png"

                }
            },

            // 2. Репозиторий сихронизирован
            State {
                name: "SYNCED"
                when: repository.GetStateListRepository[0] == "Disdsdable_sync";
                PropertyChanges {
                    target: repoSync
                    source: "qrc:/images/ok.png"
                }
            },

            // 3. Репозиторий выключен
            State {
                name: "DISABLE SYNC"
                when: repository.GetStateListRepository[0] == "Disable_sync";
                PropertyChanges {
                    target: repoSync
                    source: "qrc:/folder"

                }
            }

            // папка с автосинхронизацией контента(посмотреть, это будет отдельным состоянием, или просто как)
        ]
}
