import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    property alias nameOption: option.text
    property alias valueOption: value.text

    width: parent.width
    height: parent.height
    anchors.horizontalCenter:parent.horizontalCenter

    Text
    {
        id: option
        text: qsTr("SDFGDFfdfdf:")
    }

    Text
    {
        id: value
        text: qsTr("dffddsffdfffffff")
        anchors.left: option.right
        anchors.leftMargin: 10
    }


}
