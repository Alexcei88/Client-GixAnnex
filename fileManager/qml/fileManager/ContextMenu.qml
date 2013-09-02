import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Menu
{
    Action
    {
        id: openAction
        text: "&Open"
        shortcut: "Ctrl+O"
        //       iconSource: "images/document-open.png"
        onTriggered: { console.log("Open directory") }
        //       tooltip: "Open an image"
    }
    Action
    {
        id: getContentAction
        text: "&Get Content"
        shortcut: "Ctrl+O"
        //       iconSource: "images/document-open.png"
        onTriggered: { console.log("GetContentDirectory") }
        //       tooltip: "Open an image"
    }

    Action
    {
        id: dropContentAction
        text: "&Drop Content"
        shortcut: "Ctrl+O"
        //       iconSource: "images/document-open.png"
        onTriggered: { console.log("DropContentDirectory") }
        //       tooltip: "Open an image"
    }



    title: "ActionDirectory"
    MenuItem { action: openAction }
    MenuItem { action: getContentAction }
    MenuItem { action: dropContentAction }
    MenuItem { text: "AutoGet Content" }
    MenuItem { text: "Close" }
}



