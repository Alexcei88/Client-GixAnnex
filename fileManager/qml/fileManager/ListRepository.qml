import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
import Repository 1.0

FocusScope {

    // ФУНКЦИИ, СВО-ВА И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    property int widthRepoSync: 0
    // сигнал о выборе нового репозитория
    signal selectNewRepository(string path, string name)

    // сигнал об вкл/выкл режиме синхронизации репозитория
    signal setEnableRepository(bool enable)

    function reloadModel()
    {
        modelRepoXML.reload();
    }
    //-------------------------------------------------------------------------/
    function switchEnableRepository(enabled)
    {
        repository.setEnableRepository(enabled)
        setEnableRepository(enabled)
    }

    ControllerRepository {
        id: repository
    }

    XmlListModel
    {
        property int lastIndex: 0;
        id: modelRepoXML
        source: repository.pathRepoConfig
        query: "/reporegistry/repo"

        XmlRole { name: "localPath"; query: "@localUrl/string()"; }
        XmlRole { name: "nameRepo"; query: "@nameRepo/string()"; }

        onStatusChanged: {
            if(status === XmlListModel.Ready)
            {
                // устанавливаем индекс, который был до этого
                if(modelRepoXML.count > lastIndex)
                {
                    viewModel.currentIndex = lastIndex;
                    var localPath = modelRepoXML.get(lastIndex).localPath
                    var nameRepo = modelRepoXML.get(lastIndex).nameRepo
                    selectNewRepository(localPath, nameRepo)
                    setEnableRepository(repository.getStateRepository(localPath) !== "Disable_sincing" )
                }
                else
                {
                    setEnableRepository(false);
                }
            }
        }
    }

    SystemPalette { id: sysPal }

    id: focusScope
    Rectangle
    {
        id: rect
        color: sysPal.window
        anchors.fill: parent
        focus: true

        Menu
        {
            id: menuRepository
            title: "ActionRepository"
            Action
            {
                id: switchEnable
                text: ""
                onTriggered:
                {
                    switchEnableRepository(text === "&Enable Syncronization" ? true : false);
                }
            }
            Action
            {
                id: removeRepository
                text: "&Delete"
                shortcut: "Del"
    //            onTriggered:

            }
            MenuItem { action: switchEnable }
            MenuItem { action: removeRepository }
        }

        GridView
        {
            id: viewModel
            model: modelRepoXML

            width: parent.width

            cellHeight: 32
            cellWidth: parent.width

            anchors.fill: parent

            MouseArea {
                anchors.fill: parent
                // разрешаем распостраняться сигналу по иерархии вверх
                propagateComposedEvents: true
                onClicked: {
                    focusScope.focus = true;
                    // сигнал до конца не обработали, прокидываем по иерархии дальше
                    mouse.accepted = false;
                }
            }

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
                            state: "SYNCED"
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
                                when: { repository.getStateRepository(localPath) === "Syncing";}
                               // StateChangeScript { script: console.log("state = SYNCING") }
                                PropertyChanges {
                                    target: repoSync
                                    source: "qrc:/repo_on.png"
                                }
                            },

                            // 2. Репозиторий сихронизирован
                            State {
                                name: "SYNCED"
                                when: { repository.getStateRepository(localPath) === "Synced";}
                               // StateChangeScript { script: console.log("state = SYNCED") }
                                PropertyChanges {
                                    target: repoSync
                                    source: "qrc:/repo_on.png"
                                }
                            },

                            // 3. Репозиторий выключен
                            State {
                                name: "DISABLE SYNC"
                                when: { repository.getStateRepository(localPath) === "Disable_sincing";}
                                //StateChangeScript { script: console.log("state = DISABLE_SYNC") }
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
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true

                        onClicked: {
                            if(viewModel.currentIndex !== model.index)
                            {
                                // выбрали новый репозиторий
                                viewModel.currentIndex = model.index
                                modelRepoXML.lastIndex = model.index
                                selectNewRepository(localPath, nameRepo)
                                setEnableRepository(repository.getStateRepository(localPath) !== "Disable_sincing")
                            }
                            if(mouse.button === Qt.RightButton)
                            {
                                if(repository.getStateRepository(localPath) === "Disable_sincing")
                                    switchEnable.text = "&Enable Syncronization";
                                else
                                    switchEnable.text = "&Disable Syncronization";
                                menuRepository.popup()
                            }
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

        } // end GridView
    }
}
