import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import "utils.js" as UtilsScript
import Repository 1.0

// our stuff
import "propertyFile"

Rectangle {

    // СВО-ВА, ФУНКЦИИ И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    // функция проверки нахождения свойства folder в пределах корневого пути репозитория
    // чтобы выше корня репозитория не выходить
    function isSubRootRepositoryDirectory(folder)
    {
        return contenItem.isSubRootRepositoryDirectory(folder);
    }
    //-------------------------------------------------------------------------/
    function changeParentFolder(folder)
    {
        contenItem.changeParentFolder(folder);
    }
    //-------------------------------------------------------------------------/
    // функция показа окна ожидания клонирования
    function showWaitCommandFinish()
    {
        loaderWaitFinishCommand.setSource("repository/wait_finish_command.qml",
                                          {"itemColorOverlay" : contenItem}
                                              );
    }
    // функция скрытия окна ожидания клонирования
    function hideWaitCommandFinish()
    {
        loaderWaitFinishCommand.setSource("");
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

    property alias folderModel: contenItem.folderModel
    property alias folderView:  contenItem.folderView

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
                contenItem.changeRepository(path, name)
            }
            onSetEnableRepository: {
                contenItem.enabled = enable;
                filterDir.enabled = enable;
                if(!enable && repository.isExecuteCommandForCurrentRepository())
                {
                    showWaitCommandFinish();
                }
                else
                {
                    hideWaitCommandFinish();
                }
            }

        }
        DirectoryView
        {
            // окно ожидания выполнения команды
            id: contenItem
            objectName: "directoryView"
            Layout.minimumWidth: parent.width/4
            Layout.fillWidth: true
            width: 3 * parent.width/5
            onShowPropertyFile:
            {
                propertyFile.updateData(folder, currentName )
            }
            Loader {
                id: loaderWaitFinishCommand
                anchors.fill: parent
            }
        }

        // Вывод информации о файле(директории)
        PropertyFile
        {
            id: propertyFile
            width: parent.width/5
            Layout.minimumWidth: parent.width/5
            Layout.maximumWidth: 2 * parent.width/5
            color: sysPal.window

            // инициализация представления
            folderView: windowContent.folderView
        }
    }
}
