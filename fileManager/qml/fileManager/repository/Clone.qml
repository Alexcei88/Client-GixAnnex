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

    ColumnLayout
    {
        id: columnOptionClone
        width: parent.width
        spacing: 10

        property int widthText: 110

        RowLayout{
            anchors.leftMargin: 10
            anchors.left: parent.left
            width: parent.width

            Text{
                id: sourcePath
                text:"Source URL: "
                width: 110
            }

            TextField{
                id: soureURL
                implicitWidth: 300
                height: 20
                focus: true
                text: "cRedssssssffffffffffffffffffpo"
                anchors.left: sourcePath.right
            }

            Button {
                id: buttonSourceBrowser
                text: "Browser"
                onClicked:  {
                    console.log("dsdfd")
                }
            }
        }

        RowLayout{
            anchors.leftMargin: 10
            anchors.left: parent.left
            width: parent.width

            Text{
                id: destPath
                text:"Destinition URL: "
                width: 110
            }

            TextField{
                id: destURL
                implicitWidth: 300
                height: 20
                focus: true
                text: "home"
                anchors.left: destPath.right
            }

            Button {
                id: buttonDestBrowser
                text: "Browser"
                onClicked:  {
                    console.log("dsdfd")
                }

            }
        }
    } // end Column

    RowLayout{

        id: buttonRow
        anchors.topMargin: 15
        anchors.top: columnOptionClone.bottom

        width: parent.width
        spacing: 20
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
                }
            }
        }
    }

}

