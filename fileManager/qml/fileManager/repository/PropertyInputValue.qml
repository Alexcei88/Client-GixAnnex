import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    height: option.height
    width: option.width + value.width

    property alias nameOption: option.text
    property alias widthFieldOption: option.width
    property alias valueOption: value.text
    Text
    {
        id: option
        text: qsTr("SDFGDFfdfdf:")
        font.pixelSize: 12
    }

    TextField
    {
        id: value
        text: qsTr("")
        width: 250
        anchors.left: option.right
        anchors.leftMargin: 10
        anchors.verticalCenter: option.verticalCenter
    }
}
