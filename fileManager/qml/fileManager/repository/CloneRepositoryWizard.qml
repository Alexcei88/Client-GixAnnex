import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {

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

    Column {
        id: column
        anchors {
            left: parent.left
            right: parent.right
        }
        property int heightForPageName: 0.2 * parent.height

        Rectangle {
            border.width: 2
            radius: 10
            anchors {
                left: parent.left
                right: parent.right
            }
            height: column.heightForPageName

            // 4 как бы кнопки
            // 1 - выбор типа репозитория
            // 2 - настройки репозитория(в зависимости от типа репозитория)
            // 3 ... дополнительные поля, если нужно( у репозитория)
            // 3 - общая информация по настройкам где нажимаем начать клонирование

            ListView {
                id: view
                anchors.fill: parent
                orientation: ListView.Horizontal
                model: pageModel
                delegate: Rectangle {
                    width: button.width
                    Button {
                        id: button
                        text: title
                    }
                }
            }
        }

        StackView
        {
            id: stackView;
            height: parent.height - column.heightForPageName - 30
            anchors {
                left: parent.left
                right: parent.right
            }
            initialItem: Item {
                Text {
                    text: "VIEWERR1"
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
        /*Rectangle {
            height : 30
            width: parent.width
            border.width: 2
            color: "blue"
            anchors {
                left: parent.left
                right: parent.right
            }

            Button
            {
                text: "Backаааа"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop();
                    }
                }
            }
        }*///
    }
}


