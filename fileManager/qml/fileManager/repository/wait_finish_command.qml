import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0

ColorOverlay
{
    property var itemColorOverlay: parent
    anchors.fill: parent
    source: itemColorOverlay
    color: Qt.rgba(77/255., 113/255., 152/255., 0.4)
    Text {
        id: text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: animation.top
        anchors.bottomMargin: 10
        text: "Please wait until the command\n is finished..."
        horizontalAlignment: Text.AlignHCenter
        font.family: "Arial"
        font.pointSize: 18
    }

    AnimatedImage {
        id: animation
        asynchronous: true
        source: "qrc:/progressbar_wait_finish_command.gif"
        anchors.verticalCenterOffset: -text.implicitHeight/2
        anchors.centerIn: parent
    }
}


