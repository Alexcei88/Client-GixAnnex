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
    signal selectNewRepository(string path)

    function reloadModel()
    {
        modelRepoXML.reload();
    }
    //-------------------------------------------------------------------------/
    function switchEnableRepository(path, enabled)
    {
        repository.setEnableRepository(enabled)
        if(enabled)
        {
            console.log("Enable Repository")
        }
        else
        {
            console.log("Disable Repository")
        }
    }

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

    Rectangle
    {
        id: rect
        color: sysPal.window
        anchors.fill: parent

        Menu
        {
            id: menuRepository
            title: "ActionRepository"
            Action
            {
                id: switchEnable
                property string enableText: "&Enable Syncronization"
                text: enableText
                onTriggered:
                {
                    switchEnableRepository(text === "&Enable Syncronization" ? false : true);
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

        MouseArea {

        }

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
                                when: { repository.getStateRepository(localPath) === "Syncing";}
                                PropertyChanges {
                                    target: repoSync
                                    source: "qrc:/repo_on.png"
                                }
                            },

                            // 2. Репозиторий сихронизирован
                            State {
                                name: "SYNCED"
                                when: { repository.getStateRepository(localPath) === "Synced";}
                                PropertyChanges {
                                    target: repoSync
                                    source: "qrc:/repo_on.png"
                                }
                            },

                            // 3. Репозиторий выключен
                            State {
                                name: "DISABLE SYNC"
                                when: { repository.getStateRepository(localPath) === "Disable_sincing";}
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
                                selectNewRepository(localPath)
                            }
                            if(mouse.button === Qt.RightButton)
                            {
                                if(repoSync.state === "DISABLE_SYNC")
                                    switchEnable.enableText = "&Enable Syncronization";
                                else
                                    switchEnable.enableText = "&Disable Syncronization";
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

            Component.onCompleted:
            {
                if(GridView.isCurrentItem)
                    selectNewRepository(localPath)
            }
        }
    }
}
