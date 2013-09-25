import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
//import Repository 1.0

Rectangle {

    /*ControllerRepository {
        id: repository
    }*/
    width: 100
    height: 62
    border.width: 1
    border.color: "black"
    radius: 2

    XmlListModel{
        id: modelRepoXML
//        source: "../../ganx-repository.xml"
        source: "qrc:/config/config_repo"
        query: "/reporegistry/repo"

        XmlRole { name: "localPath"; query: "@localURL/string()" }
        XmlRole { name: "nameRepo"; query: "@nameRepo/string()" }

    }

    ListView {

        width: parent.width
        height: parent.height
        Component.onCompleted: {
            console.log("Competed Component ListView Repository")
            console.log(modelRepoXML.errorString())
        }

        model: modelRepoXML
        delegate:
                Text {
                text: nameRepo
            }
    }
}
