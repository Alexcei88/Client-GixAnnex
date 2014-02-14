import QtQuick 2.1
import QtQuick.XmlListModel 2.0

Item {

    XmlListModel
    {
        id: modelRepoXML
        source: "qrc:/config/config_list_repository"
        query: "/list_repository/repo"
        XmlRole { name: "nameRepo"; query: "@name/string()"; }
        onStatusChanged:  {
            console.log("Status change" + status)
        }
    }

    ListView
    {
        id: viewCloud
        model: modelRepoXML
        anchors.fill: parent
        Component.onCompleted: {
            console.log("ComponentOnCompleted")
        }

        delegate: Text {
                property var curName: nameRepo

                text: curName
                color: "#00FF00"
                Component.onCompleted:
                {
                    console.log("name = " + curName);
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Change scena");
                        stackView.push(Qt.resolvedUrl("ssh_user_data.qml"))
                    }
                }
            }
    }
}
