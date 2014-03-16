import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import QtQuick.XmlListModel 2.0

import Repository 1.0
import Message 1.0
import TreeModel 1.0

Rectangle {

    // размер шрифта заголовков
    property int sizeFontHead: 18

    // размер шрифта текста с деталями копирования
    property int sizeFontTextDetails: 18

    ControllerAddRepository{
        id: addRepository
    }

    MessageBox
    {
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
        XmlRole { name: "indexRepo"; query: "@index/string()"; }
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
        XmlRole { name: "indexRepo"; query: "@index/string()"; }
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

    TreeModel {
        id: pageModel
    }

    // 5 минимальных полей
    // 1 - выбор типа репозитория
    // 2 - настройки репозитория(в зависимости от типа репозитория)
    // 3 - общая информация по настройкам где нажимаем начать клонирование
    // 4 - процесс клонирования
    // 5 - окончание клонирования

    color: sysPal.window

    Rectangle {
        id: menu
        anchors {
            left: parent.left
            bottom: separatorRect.top
            bottomMargin: 10
            top: parent.top
        }
        width: parent.width/4

        RadialGradient {
            anchors.fill: parent
            gradient: Gradient {
                //                GradientStop { position: 0.0; color: "#0095b6" }
                GradientStop { position: 0.0; color: "#007fff" }
                GradientStop { position: 1.0; color: "white" }
            }
            horizontalOffset: -200
            verticalOffset: parent.width
            angle: 0
            verticalRadius: 400
            horizontalRadius: 300
        }

        // отображаем наше дерево
        ListView {
            id: treeView
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.leftMargin: 2
            model: pageModel
            spacing: 5
            delegate: treeDelegate
            interactive: false
            currentIndex: 0

            Item {
                id: markNode
                anchors.left: parent.left
                x: treeView.currentItem.x
                y: treeView.currentItem.y
                width: imageMarkNode.implicitWidth

                Image {
                    id: imageMarkNode
                    source: "qrc:/node_closed.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            treeView.currentIndex++;
                        }
                    }
                }
            }

            Component {
                id: treeDelegate                

                Item {
                    id: wrapper
                    property bool isCurrent: ListView.isCurrentItem

                    height: 20
                    width: treeView.width

                    //"Отбой" слева элементов-потомков
                    Item {
                        id: levelMarginElement
                        //Начиная с 6 уровня вложенности не сдвигаем потомков,
                        //так как иначе можно получить очень широкое окно
                        width: (level> 5 ? 6: level)* 32 + 5
                        anchors.left: parent.left
                        anchors.leftMargin: markNode.width
                    }
                    //Область для открытия/закрытия потомков.
                    //На листьях не виден
                    Item {
                        id: nodeOpenElement
                        anchors.left: levelMarginElement.right
                        anchors.verticalCenter: wrapper.verticalCenter
                        height: 24
                        state: "leafNode"
                        Image {
                            id: triangleOpenImage
                            //Отлавливаем нажатие мышкой и открываем/закрываем элемент
                            MouseArea {
                                anchors.fill: parent
                                onClicked: { (isOpened) ?
                                                 pageModel.closeItem(index) :
                                                 pageModel.openItem(index)
                                            }
                            }
                        }
                        states: [
                            //Лист
                            //Область не видна
                            State {
                                name: "leafNode"
                                when: !hasChildren
                                PropertyChanges {
                                    target: nodeOpenElement
                                    visible: false
                                    width: 0
                                }
                            },
                            //Открытый элемент
                            //Область видна и отображена соответствующая иконка
                            State {
                                name: "openedNode"
                                when: (hasChildren)&&(isOpened)
                                PropertyChanges {
                                    target: nodeOpenElement
                                    visible: true
                                    width: 32
                                }
                                PropertyChanges {
                                    target: triangleOpenImage
                                    source: "qrc:/node_opened.png"
                                }
                            },
                            //Закрытый элемент
                            //Область видна и отображена соответствующая иконка
                            State {
                                name: "closedNode"
                                when: (hasChildren)&&(!isOpened)
                                PropertyChanges {
                                    target: nodeOpenElement
                                    visible: true
                                    width: 32
                                }
                                PropertyChanges {
                                    target: triangleOpenImage
                                    source: "qrc:/node_closed.png"
                                }
                            }
                        ]
                    }
                    //Область для отображения данных элемента
                    Text {
                        id: nameTextElement
                        text: name
                        verticalAlignment: "AlignVCenter"
                        anchors.left: nodeOpenElement.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        font {
                            bold: isCurrent
                        }
                    }
                } // end Item
            } // end Component
        }
    }

    StackView
    {
        // все страницы должны реализовывать функции
        // 1. перехода на следующую страницу nextPage();
        // 2. переход на предыдущую страницу prevPage();
        // 3. актуализации кнопок интерфейса updateUI();

        id: stackView
        objectName: "StackView"

        property int selectIndexRepository: -1
        anchors {
            bottom: separatorRect.top
            bottomMargin: 10
            top: parent.top
            left: menu.right
            right: parent.right
        }
        initialItem: Qt.resolvedUrl("list_repositories.qml");

        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
                properties.enterItem.updateUI();
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
    // разделитель(взят из ToolBarStyle)
    Rectangle {
        id: separatorRect
        height: 1
        color: "#999"
        anchors.bottom: managerPanel.top
        anchors.right: parent.right
        anchors.left: parent.left
    }

    Rectangle {
        id: managerPanel
        anchors {
            left: parent.left
            bottom: parent.bottom
            right: parent.right
        }
        height: 55
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
                        if(stackView.depth == 2)
                        {
                            // выключаем кнопку назад и вперед
                            buttonBack.enabled = false;
                            buttonNext.enabled = false;
                            // мы в самом начале, индекс скидываем
                            treeView.currentIndex = 0;
                        }
                        else
                        {
                            stackView.currentItem.prevPage();
                        }
                        stackView.pop();

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
            field.wasErrorValue = true;
            errorString.val = "Field <i>" + field.nameOption.substring(0, field.nameOption.length - 1)
                                + "</i>" + " not must to be empty";
            return false;
        }
        field.wasErrorValue = false;
        errorString.val = "";
        return true;
    }

}


