import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Rectangle
{
    property string initText: "start clone"
    objectName: "waitClone"

    function nextPage()
    {

    }

    function actualizeButton()
    {        
        buttonBack.enabled = false;
        buttonNext.enabled = false;
        buttonBack.visible = false;
        buttonNext.visible = false;
    }

    function resultAddRepository(text)
    {
        console.log("End Clone Repository");
        textArea.append(text);
//        textArea.select(0, 6);
        // выделить только последнюю строчку
//        textArea.textColor = "red";
       // textArea.deselect();
        buttonCancel.text = "Finish";
    }

    SystemPalette { id: sysPal }
    color: sysPal.window

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        ProgressBar{
            id: progressBar
            indeterminate: true
            anchors.right: parent.right
            anchors.left: parent.left
        }
        TextArea{
            id: textArea
            anchors.top: progressBar.bottom
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            text: initText
            readOnly: true
            textColor: "blue"
        }

    }
}

