import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Menu
{
    // Меню будет отправлять соот сигналы, а в файле приемнике будет обработка нужной функцией
    signal openDirectory()
    signal getContentDirectory()
    signal dropContentDirectory()

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
        //       tooltip: "Open an image"
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
        //       tooltip: "Open an image"
    }



    title: "ActionDirectory"
    MenuItem { action: openAction }
    MenuItem { action: getContentAction }
    MenuItem { action: dropContentAction }
    MenuItem { text: "On/Off autoget content" }
    MenuItem { text: "Close" }
}



