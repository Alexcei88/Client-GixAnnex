import QtQuick 2.1
import QtQuick.Layouts 1.1

Rectangle {

    function actualizeButton()
    {

    }

    color: sysPal.window

    Component {

        id: contactDelegate
        Item {
            id: delegateItem
            property var curName: nameRepo
            property var curDescription: descriptionRepo
            property var curNextUrl: url1

            height: textLink.height + txtDescription.height

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
                            if(delegateItem.curNextUrl != "")
                            {
                                stackView.selectIndexRepository = model.index;
                                // сначала фиксируем, что был выбран удаленный репозиторий
                                addRepository.selectServer(model.index);
                                stackView.push({ item: Qt.resolvedUrl(delegateItem.curNextUrl), destroyOnPop: true})
                                // включаем кнопки назад или вперед
                                buttonBack.enabled = true;
                                buttonNext.enabled = true;
                            }
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
        }
    } // end Component

    Column {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 20
        anchors.topMargin: 15
        anchors.right: parent.right
        anchors.left: parent.left

        ListView
        {
            id: viewCloud
            model: modelRepoXMLCloud
            height: 100
            anchors
            {
                left: parent.left
                right: parent.right
            }

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

            delegate: contactDelegate
        }
        // локальный репозитории
        ListView
        {
            id: viewLocal
            model: modelRepoXMLLocal
            height: 100
            anchors
            {
                topMargin: 10
                top: viewCloud.bottom
            }
            spacing: 10

            header:
                Text {
                id: headGroupLocal
                text: qsTr("Add local repository")
                font{
                    bold: true
                    pixelSize: 18
                    weight: Font.DemiBold
                }
            }

            delegate: contactDelegate
        }
    }
}
