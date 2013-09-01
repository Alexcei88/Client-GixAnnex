import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0


Rectangle {
    width: 100
    height: 62

    SplitView
    {
        id: split
        anchors.fill: parent
        orientation: Qt.Horizontal
        Rectangle {
            width: parent.width/5
            Layout.minimumWidth: parent.width/8
            Layout.maximumWidth: 3 * parent.width/5
            color: "gray"
        }
        Rectangle {
            id: centerItem
            Layout.minimumWidth: parent.width/5
            Layout.fillWidth: true
            color: "darkgray"
            width: 3 * parent.width/5
        }

        Rectangle{
            id: option
            width: parent.width/5
            Layout.minimumWidth: parent.width/5
            Layout.maximumWidth: 3 * parent.width/5
            color: "green"
        }
    }



}
