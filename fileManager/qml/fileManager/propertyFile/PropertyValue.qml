import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    property alias nameOption: option.text
    property alias widthFieldOption: option.width
    property alias valueOption: value.text
    property int sizeFont: 10
    anchors.horizontalCenter: parent.horizontalCenter
    height: option.implicitHeight + value.implicitHeight

    Text
    {
        id: option
        text: qsTr("SDFGDFfdfdf:")
        font.pixelSize: sizeFont
        wrapMode: Text.WrapAnywhere
    }

    Text
    {
        id: value
        text: qsTr("")
        font.pixelSize: sizeFont
        anchors.left: option.right
        anchors.leftMargin: 10
        width: parent.width - widthFieldOption
        wrapMode: Text.WrapAnywhere
    }


}
