import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    id: mainItem
    height: option.height
    width: option.width + value.width

    property alias nameOption: option.text
    property alias widthFieldOption: option.width
    property alias valueOption: value.text
    property bool errorValue: false

    signal textChange;

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

        onTextChanged:
        {
            mainItem.textChange;
        }

        BorderImage {
            source: "qrc:images/lineedit_bg_error.png"
            width: parent.width; height: parent.height
            border { left: 4; top: 4; right: 4; bottom: 4 }
            visible: mainItem.errorValue
        }
    }
}
