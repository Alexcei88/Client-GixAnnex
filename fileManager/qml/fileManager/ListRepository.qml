import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
import Repository 1.0

Rectangle {

    ControllerRepository {
        id: repository
    }

    // ФУНКЦИИ, СВО-ВА И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    // сигнал о выборе нового репозитория
    signal selectNewRepository(string path)

    // сигнал о перегрузке модели в связи с изменениями
    signal reloadModel()
    onReloadModel: {
        modelRepoXML.reload();
    }

    //-------------------------------------------------------------------------/

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

        currentIndex: -1
        anchors.fill: parent

        keyNavigationWraps: true
        highlight: Rectangle {
            color: "skyblue"
            radius: 1
            anchors.margins: 20
        }
        highlightMoveDuration: 0
        delegate:
            Item{
            id: viewItem
            height: viewModel.cellHeight
            width: viewModel.cellWidth
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
}
