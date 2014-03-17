import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item
{
    Window {
        id: waitWindow
        title: "Please Wait..."
        width: 640
        height: 480
        visible: true
        // когда появляеться это окно, все остальные окна перестают принимать сообщения
        modality: Qt.ApplicationModal

        RowLayout
        {
	    anchor.centerIn: parent 
            ProgressBar{
                id: progressBar
                indeterminate: true
                value: 1
                widht: parent.width/5
            }
        }
    }
}

