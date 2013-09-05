import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

// our stuff
import "propertyFile"

Rectangle {
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

        Rectangle
        {
            width: parent.width/5
            Layout.minimumWidth: parent.width/8
            Layout.maximumWidth: 3 * parent.width/5
            color: "gray"
        }
        DirectoryView
        {
            id: contenItem
            Layout.minimumWidth: parent.width/5
            Layout.fillWidth: true
            color: "darkgray"
            width: 3 * parent.width/5
            focus: true
            onShowPropertyFile: { propertyFile.updateData(currentName) }
        }

        // Вывод информации о файле,директории
        PropertyFile
        {
            id: propertyFile
            width: parent.width/5
            Layout.minimumWidth: parent.width/5
            Layout.maximumWidth: 3 * parent.width/5
            color: '#116062'

            // нициализация представления
            folderView: windowContent.folderView
        }
    }



}
