import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0

import Repository 1.0

Rectangle {

    ControllerAddRepository{
        id: addRepository
    }

    SystemPalette { id: sysPal }

    XmlListModel
    {
        id: modelRepoXMLCloud
        source: "qrc:/config/config_list_repository_cloud"
        query: "/list_repository/repo"
        XmlRole { name: "nameRepo"; query: "@name/string()"; }
        XmlRole { name: "descriptionRepo"; query: "@description/string()"; }
        XmlRole { name: "url1"; query: "optionURL/url[1]/string()"; }
        XmlRole { name: "url2"; query: "optionURL/url[2]/string()"; }
        XmlRole { name: "url3"; query: "optionURL/url[3]/string()"; }
        XmlRole { name: "url4"; query: "optionURL/url[4]/string()"; }
        XmlRole { name: "url5"; query: "optionURL/url[5]/string()"; }
        XmlRole { name: "url6"; query: "optionURL/url[6]/string()"; }
        XmlRole { name: "url7"; query: "optionURL/url[7]/string()"; }
        XmlRole { name: "url8"; query: "optionURL/url[8]/string()"; }
        XmlRole { name: "url9"; query: "optionURL/url[9]/string()"; }
        XmlRole { name: "url10"; query: "optionURL/url[10]/string()"; }
        XmlRole { name: "url_review"; query: "optionURL/url_review/string()"; }
    }

    // репы, которые локальные
    XmlListModel
    {
        id: modelRepoXMLLocal
        source: "qrc:/config/config_list_repository_local"
        query: "/list_repository/repo"
        XmlRole { name: "nameRepo"; query: "@name/string()"; }
        XmlRole { name: "descriptionRepo"; query: "@description/string()"; }
        XmlRole { name: "url1"; query: "optionURL/url[1]/string()"; }
        XmlRole { name: "url2"; query: "optionURL/url[2]/string()"; }
        XmlRole { name: "url3"; query: "optionURL/url[3]/string()"; }
        XmlRole { name: "url4"; query: "optionURL/url[4]/string()"; }
        XmlRole { name: "url5"; query: "optionURL/url[5]/string()"; }
        XmlRole { name: "url6"; query: "optionURL/url[6]/string()"; }
        XmlRole { name: "url7"; query: "optionURL/url[7]/string()"; }
        XmlRole { name: "url8"; query: "optionURL/url[8]/string()"; }
        XmlRole { name: "url9"; query: "optionURL/url[9]/string()"; }
        XmlRole { name: "url10"; query: "optionURL/url[10]/string()"; }
        XmlRole { name: "url_review"; query: "optionURL/url_review/string()"; }
    }

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

        property int selectIndexRepository: -1
        anchors {
            bottom: managerPanel.top
            top: parent.top
            left: head.right
            right: parent.right
        }
        initialItem: Qt.resolvedUrl("list_repositories.qml");

        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
                properties.enterItem.actualizeButton();
            }

            property Component pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }
        }
    }

    // все страницы должны реализовывать функции
    // 1. перехода на следующую страницу nextPage();
    // 2. актуализации кнопок интерфейса actualizeButton();

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
            spacing: 20
            anchors.fill: parent
            anchors.rightMargin: 20
            layoutDirection: Qt.RightToLeft

            Button {
                id: buttonCancel
                text: qsTr("Cancel")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {

                    }
                }
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                id: buttonNext
                enabled: false
                text: qsTr("Next >")
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.currentItem.nextPage();
                    }
                }
            }
            Button {
                id: buttonBack
                enabled: false
                text: qsTr("< Back")
                anchors.verticalCenter: parent.verticalCenter
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop();
                        if(stackView.depth == 1)
                        {
                            // выключаем кнопку назад и вперед
                            buttonBack.enabled = false;
                            buttonNext.enabled = false;
                        }
                    }
                }
            }
        } // end Row
    }
    // функция на проверку пустого значения в компонете PropertyValue
    function checkForEmpty(field)
    {
        if(field.valueOption === "")
        {
            console.log("ffff");
            return false;
        }
        return true;
    }

}


