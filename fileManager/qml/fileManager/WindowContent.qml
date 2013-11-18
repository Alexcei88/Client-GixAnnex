import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "utils.js" as UtilsScript

// our stuff
import "propertyFile"

Rectangle {

    // СВО-ВА, ФУНКЦИИ И СИГНАЛЫ
    //-------------------------------------------------------------------------/
    // обновление списка состояния синхронизации файлов у DirectoryView
    function updateListFileSync(folder)
    {
        contenItem.updateListStateFileSync(folder);
    }

    // функция проверки нахождения свойства folder впределах корневого пути репозитория
    // чтобы выше корня репозитория не выходить
    function direcotoryIsSubRootRepositoryDirectory(folder)
    {
        return contenItem.direcotoryIsSubRootRepositoryDirectory(folder);
    }
    //-------------------------------------------------------------------------/

    id: windowContent
    width: 100
    height: 62

    property var folderModel: contenItem.folderModel
    property var folderView:  contenItem.folderView

    Keys.forwardTo: [split]

    SplitView
    {
        id: split
        anchors.fill: parent
        orientation: Qt.Horizontal
        focus: true
        Keys.forwardTo: [contenItem]

        // функция перезагрузки модели списка репозиториев
        function reloadModel()
        {
            listRepository.reloadModel();
        }

        ListRepository
        {
            id: listRepository
            width: parent.width/5
            Layout.minimumWidth: parent.width/8
            Layout.maximumWidth: 3 * parent.width/5
            color: "#E6E6FA"
            onSelectNewRepository:
            {
                contenItem.changeParentFolder(path)
                propertyFile.folderPath = path;
            }
        }
        DirectoryView
        {
            id: contenItem
            objectName: "directoryView"
            Layout.minimumWidth: parent.width/5
            Layout.fillWidth: true
            color: "darkgray"
            width: 3 * parent.width/5
            focus: true
            onShowPropertyFile:
            {
                propertyFile.folderPath = UtilsScript.GetFullStrPath(folderModel.folder.toString());
                propertyFile.updateData(currentName)
            }
        }

        // Вывод информации о файле,директории
        PropertyFile
        {
            id: propertyFile
            width: parent.width/5
            Layout.minimumWidth: parent.width/5
            Layout.maximumWidth: 3 * parent.width/5
            color: '#116062'

            // инициализация представления
            folderView: windowContent.folderView
        }
    }



}
