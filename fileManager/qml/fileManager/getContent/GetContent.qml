import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

ApplicationWindow{
        id: rect
        x: 10
        y: 200
        width: 100
        height: 62

        ProgressBar{
            id: loadFileProgress
            width: parent.width/2
            height: 20
            value: 0.5

        }

    }
