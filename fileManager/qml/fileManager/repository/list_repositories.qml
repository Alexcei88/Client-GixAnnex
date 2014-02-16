import QtQuick 2.1
import QtQuick.XmlListModel 2.0
import QtQuick.Layouts 1.1

Rectangle {

    color: sysPal.window

    XmlListModel
    {
        id: modelRepoXML
        source: "qrc:/config/config_list_repository_cloud"
        query: "/list_repository/repo"
        XmlRole { name: "nameRepo"; query: "@name/string()"; }
        XmlRole { name: "descriptionRepo"; query: "@description/string()"; }
        XmlRole { name: "nextUrl"; query: "@option/url/destinition/string()"; }
    }

    ListView
    {
        id: viewCloud
        model: modelRepoXML
        anchors.fill: parent
        anchors.margins: 20
        anchors.topMargin: 15
        spacing: 10

        header:
            Text {
                id: headGroup
                text: qsTr("Store your data in the cloud")
                font{
                    bold: true
                    pixelSize: 18
                    weight: Font.DemiBold
                }
            }

        delegate:
                Item {
                    id: delegateItem
                    property var curName: nameRepo
                    property var curDescription: descriptionRepo
                    property var curNextUrl: nextUrl

                    height: textLink.height + txtDescription.height

                    Component.onCompleted: {
                        console.log(curNextUrl);
                    }

                    Column {
                        Text {
                            id: textLink

                            text: curName
                            font {
                                bold: true
                                pixelSize: 14
                            }
                            color: "#008cf0"

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    stackView.push(Qt.resolvedUrl("ssh_user_data.qml"))
                                }
                                onEntered: {
                                    textLink.font.underline = true;
                                }
                                onExited: {
                                    textLink.font.underline = false;
                                }
                            }
                        }
                        Text {
                            id: txtDescription
                            text: descriptionRepo
                            font {
                                pixelSize: 12
                            }
                        }
                    } // end Column
        } // end Item
    }
}
