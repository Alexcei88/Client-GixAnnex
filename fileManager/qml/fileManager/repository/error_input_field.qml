import QtQuick 2.0

Rectangle {

    id: mainRect
    property string textError: "Text Example"

    width: 200
    height: text.contentHeight + 6
    color: "#ffe2e1"
    anchors.verticalCenter: parent.verticalCenter
    anchors.centerIn: parent
    border.color: "#808080"
    border.width: 1
    radius: 4

    Text {
        id: text
        anchors.fill: parent
        anchors.margins: 2
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.centerIn: parent
        text: textError
        color: "red"
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        wrapMode: Text.WordWrap
    }
}
