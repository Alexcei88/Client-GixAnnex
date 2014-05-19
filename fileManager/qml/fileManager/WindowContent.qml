import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import "utils.js" as UtilsScript
import Repository 1.0

// our stuff
import "propertyFile"

Rectangle {

    objectName: "windowContent"

    // СВО-ВА, ФУНКЦИИ И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    // функция проверки нахождения свойства folder в пределах корневого пути репозитория
    // чтобы выше корня репозитория не выходить
    function isSubRootRepositoryDirectory(folder)
    {
        return contenItem.get(0, true).isSubRootRepositoryDirectory(folder);
    }
    //-------------------------------------------------------------------------/
    function changeParentFolder(folder)
    {
        contenItem.get(0, true).changeParentFolder(folder);
    }
    //-------------------------------------------------------------------------/
    ControllerRepository {
        id: repository
    }

    SystemPalette { id: sysPal }

    id: windowContent
    width: 100
    height: 62
    color: sysPal.window

    property var folderModel: 0
    property var folderView:  0

    //-------------------------------------------------------------------------/
//    // функция показа окна ожидания клонирования
//    function showWaitCommandFinish()
//    {
//        loaderWaitFinishCommand.setSource("repository/wait_finish_command.qml",
//                                          {"itemColorOverlay" : contenItem}
//                                          );
//    }
//    // функция скрытия окна ожидания клонирования
//    function hideWaitCommandFinish()
//    {
//        loaderWaitFinishCommand.setSource("");
//    }
//    //-------------------------------------------------------------------------/

    SplitView
    {
        id: split
        anchors.fill: parent
        orientation: Qt.Horizontal

        ListRepository
        {
            id: listRepository
            objectName: "listRepository"
            width: parent.width/5
            Layout.minimumWidth: parent.width/8
            Layout.maximumWidth: parent.width/4
            onSelectNewRepository:
            {
                contenItem.get(0, true).changeRepository(path, name)
            }
            onSetEnableRepository: {
                contenItem.get(0, true).enabled = enable;
                filterDir.enabled = enable;
                if(!enable && repository.isExecuteCommandForCurrentRepository())
                {
                    showWaitCommandFinish();
                }
            }

        }

        StackView
        {
            // стэк вью с главной частю экрана
            objectName: "contentItemView"

            // модель ошибки
            ListModel {
                id: modelAllError
            }

            // добавление в модель новой ошибки
            function appendError(description, nameRepository)
            {
                modelAllError.append({"description" : description,
                                      "nameRepo" : nameRepository
                                     });
                showErrorView();
            }
            // показать окно с ошибками
            function showErrorView()
            {
                if(contenItem.currentItem.objectName != "errorView")
                {
                    contenItem.push({ item: Qt.resolvedUrl("ErrorView.qml"), destroyOnPop: true,
                                properties: { modelError: modelAllError}
                                });
                }
            }

            function hideErrorView()
            {
                if(contenItem.currentItem.objectName == "errorView")
                {
                    contenItem.pop();
                }
            }

            property alias propertyFile: propertyFile

            id: contenItem
            Layout.minimumWidth: parent.width/4
            Layout.fillWidth: true
            width: 3 * parent.width/5

            initialItem: Qt.resolvedUrl("DirectoryView.qml");

            Component.onCompleted:
            {
                var item = get(0, true);
                propertyFile.folderView = item.folderView;
                windowContent.folderView = item.folderView;
                windowContent.folderModel = item.folderModel;
            }
//            Loader {
//                id: loaderWaitFinishCommand
//                anchors.fill: parent
//            }

        }

        // Вывод информации о файле(директории)
        PropertyFile
        {
            id: propertyFile
            width: parent.width/5
            Layout.minimumWidth: parent.width/5
            Layout.maximumWidth: 2 * parent.width/5
            color: sysPal.window

        }
    }
}
