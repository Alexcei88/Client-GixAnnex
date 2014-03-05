import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0

import Repository 1.0
import Message 1.0

Rectangle {

    ControllerAddRepository{
        id: addRepository
    }

    MessageBox{
        id: message
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
    }

    // общие параметры
    XmlListModel
    {
        id: modelRepoXMLCommon
        source: "qrc:/config/config_list_repository_common"
        query: "/optionURL"
        XmlRole { name: "url_save"; query: "url_save/string()"; }
        XmlRole { name: "url_review"; query: "url_review/string()"; }
        XmlRole { name: "url_addrepo"; query: "url_addrepo/string()"; }
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
        objectName: "StackView"

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
        // результат клонирования
        function resultClone(text)
        {
            stackView.currentItem.resultAddRepository(text);
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
                        if(buttonCancel.text == "Finish")
                        {
                            addRepository.closeAddRepository();
                        }
                        else {
                        var text = "Do you really want to cancel add a repository?<br>"
                        if(message.showConfirmMessage("Warning", text))
                            addRepository.closeAddRepository();
                        }
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
    function checkForEmpty(field, errorString)
    {
        if(field.valueOption === "")
        {
            field.errorValue = true;
            errorString = "Field <i>" + field.nameOption + "</i>" + " not must to be empty";
            return false;
        }
        field.errorValue = false;
        errorString = "";
        return true;
    }

}


