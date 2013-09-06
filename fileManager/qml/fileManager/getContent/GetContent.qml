import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

Window{
        id: rect
        x: 10
        y: 200
        width: 100
        height: 62
        title: "Processing get content "
        modality: Qt.ApplicationModal
//        flags: Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.BypassWindowManagerHint | Qt.BypassGraphicsProxyWidget | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint | Qt.Tool | Qt.WindowCloseButtonHint
        flags: Qt.Dialog | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint
        Column
        {
            Text{
                id: nameFile
                text:"fsdfd"
            }

            ProgressBar{
                id: loadFileProgress
                width: parent.width
                height: 20
                value: 0.5
            }
            Button{
                id: cancelButton
                text: "Cancel"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("Cancel load")
                        rect.close();
                    }
                }
            }
        }

    }

