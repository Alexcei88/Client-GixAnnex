import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Menu
{
    property bool isPopup: false

    // Меню будет отправлять соот сигналы, а в файле приемнике будет обработка нужной функцией
    signal openDirectory()
    signal getContentDirectory()
    signal dropContentDirectory()
    signal removeDirectory()

    Action
    {
        id: openAction
        text: "&Open"
        shortcut: "Ctrl+O"
        //       iconSource: "images/document-open.png"
        onTriggered: {
            // посылаем сигнал открыть директорию
            openDirectory()
        }
    }
    Action
    {
        id: getContentAction
        text: "&Get Content"
        shortcut: "Ctrl+G"
        //       iconSource: "images/document-open.png"
        onTriggered: {
            getContentDirectory()
        }
    }

    Action
    {
        id: dropContentAction
        text: "&Drop Content"
        shortcut: "Ctrl+D"
        //       iconSource: "images/document-open.png"
        onTriggered: {
            dropContentDirectory()
        }
    }

    Action
    {
        id: removeDirectoryAction
        text: "&Delete"
        shortcut: "Del"
        //       iconSource: "images/document-open.png"
        onTriggered: {
            removeDirectory()
        }
    }

    title: "ActionDirectory"
    MenuItem { action: openAction }
    MenuItem { action: getContentAction }
    MenuItem { action: dropContentAction }
    MenuItem { action: removeDirectoryAction }

    onPopupVisibleChanged:{
        isPopup = !isPopup;
    }
}



