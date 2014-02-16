import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {

    SystemPalette { id: sysPal }

    // модель, содержащая список view, которые будут
    // отображаться в стек-вью
    ListModel {
        id: pageModel
        ListElement {
            title: "Select Type"         // текст сообщения, который отображается когда отображаем этот viewer
            urlComponent: "bla-bla-bla" // url репозитория, откуда загружать viewer
        }
        ListElement {
            title: "Options"
            urlComponent: "bla-bla-bla"
        }
        ListElement {
            title: "Reviewer"
            urlComponent: "bla-bla-bla"
        }
    }

//            // 4 как бы кнопки
//            // 1 - выбор типа репозитория
//            // 2 - настройки репозитория(в зависимости от типа репозитория)
//            // 3 ... дополнительные поля, если нужно( у репозитория)
//            // 3 - общая информация по настройкам где нажимаем начать клонирование

    Rectangle {
        id: head
        anchors {
            left: parent.left
            bottom: parent.bottom
            top: parent.top
        }

        width: parent.width/4

        // 4 как бы кнопки
        // 1 - выбор типа репозитория
        // 2 - настройки репозитория(в зависимости от типа репозитория)
        // 3 ... дополнительные поля, если нужно( у репозитория)
        // 3 - общая информация по настройкам где нажимаем начать клонирование

        ListView {
            id: view
            anchors.fill: parent
            model: pageModel
            delegate: Text {
                    text: title
            }
        }
    }

    StackView
    {
        id: stackView
        anchors {
            bottom: managerPanel.top
            top: parent.top
            left: head.right
            right: parent.right
        }
        initialItem: Qt.resolvedUrl("list_repositories.qml");
    }

    Rectangle {
        id: managerPanel
        anchors {
            left: parent.left
            bottom: parent.bottom
            right: parent.right
        }
        height: 50
        color: sysPal.window

        Row {
            id: rowButton
            width: parent.width
            height: parent.height
            spacing: 30
            anchors.right: parent.right
            anchors.rightMargin: 10

            Button {
                id: buttonBack
                enabled: false
                text: qsTr("Back")

            }
            Button {
                id: buttonNext
                enabled: false
                text: qsTr("Next")
            }
            Button {
                id: buttonFinish
                text: qsTr("Finish")
            }
            Button {
                id: buttonCancel
                text: qsTr("Cancel")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {

                    }
                }
            }


        } // end Row
    }
}


