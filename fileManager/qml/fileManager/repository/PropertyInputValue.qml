import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    id: mainItem
    height: value.implicitHeight
    width: option.width + value.width

    property alias nameOption: option.text
    property alias widthFieldOption: option.width
    property alias valueOption: value.text
    property bool wasErrorValue: false
    property var textValidator: RegExpValidator { regExp: /.*/ }
    property alias acceptedInput: value.acceptableInput
    property alias readonly: value.readOnly

    Text
    {
        id: option
        text: wasErrorValue ? (text + "ffff") : text
        font.pixelSize: 12
        color: wasErrorValue ? "red" : "black"
    }

    TextField
    {
        id: value
        text: qsTr("")
        width: 250
        anchors.left: option.right
        anchors.leftMargin: 10
        anchors.verticalCenter: option.verticalCenter
        validator: textValidator

        BorderImage {
            source: "qrc:images/lineedit_bg_error.png"
            width: parent.width; height: parent.height
            border { left: 4; top: 4; right: 4; bottom: 4 }
            visible: mainItem.wasErrorValue
        }
    }
}
