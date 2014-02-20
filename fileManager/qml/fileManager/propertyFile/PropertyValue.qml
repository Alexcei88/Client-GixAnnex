import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    property alias nameOption: option.text
    property alias widthFieldOption: option.width
    property alias valueOption: value.text
    property alias sizeFont: option.font.pixelSize

    anchors.horizontalCenter: parent.horizontalCenter
    Text
    {
        id: option
        text: qsTr("SDFGDFfdfdf:")
        font.pixelSize: 10
    }

    Text
    {
        id: value
        text: qsTr("")
        font.pixelSize: 10
        anchors.left: option.right
        anchors.leftMargin: 10
    }


}
