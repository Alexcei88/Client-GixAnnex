import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import Repository 1.0

Rectangle
{
    ControllerRepository {
        id: repository
    }

    id: rect
    x: 0
    y: 0
    width: 100
    height: 62
    //        title: "Processing get content "
    //        modality: Qt.ApplicationModal
    //        flags: Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.BypassWindowManagerHint | Qt.BypassGraphicsProxyWidget | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint | Qt.Tool | Qt.WindowCloseButtonHint
    //        flags: Qt.Dialog | Qt.WindowStaysOnTopHint | Qt.X11BypassWindowManagerHint
    Column
    {
        RowLayout{

            Text{
                id: nameFile
                text:"Repository URL:"
            }

            TextField{
                id: urlRepo
                width: parent.width
                height: 20
                focus: true
                text: "cloneRepo"
            }

        }

        Row{

            id: buttonRow
//            anchors.left: parent.left
//            anchors.right: parent.right
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter

            Button{
                id: cloneButton
                text: "Clone"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("Start Clone")
                        repository.StartCloneRepository()
                    }
                }
            }

            Button{
                id: cancelButton
                text: "Cancel"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("Cancel Clone")
                        //rect.close();
                    }
                }
            }
        }
    }
}

