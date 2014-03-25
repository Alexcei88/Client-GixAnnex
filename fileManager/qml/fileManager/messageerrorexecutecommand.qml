import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {
    width: parent.width
    height: parent.height
    Row {
        Text {
            id: textMessage
            text:"message"
        }
        Button {
            text: "Skip"
        }
        Button {
            text: "Execute Action"
        }
    }
}
