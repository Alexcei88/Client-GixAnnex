import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0

Rectangle {
    objectName: "errorView"

    width: 100
    height: 62

    property var modelError: 0

    Rectangle
    {
        SystemPalette { id: sysPal }
        color: sysPal.window
        anchors.fill: parent

        ScrollView
        {
            anchors {
                fill: parent
            }

            ListView
            {
                anchors {
                    fill: parent
                }

                model: modelError

                delegate:
                    Rectangle
                    {
                        id: itemView
                        property bool isCurrent: GridView.isCurrentItem

                        color: "#faf0e6"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: column.height + 2 * column.anchors.margins
                        border.width: 1
//                        border.color: "#42aaff"
                        border.color: "#808080"
                        radius: 2

                        function removeError()
                        {
                            modelError.remove(model.index);
                            if(modelError.count == 0)
                            {
                                contenItem.pop();
                            }
                        }
                        Column
                        {
                            id: column
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.margins: 15
                            spacing: 5
                            Text {
                                id: desctiption
                                text: description
                                font
                                {
                                    pixelSize: 20
                                }
                                anchors
                                {
                                    right: parent.right
                                    left: parent.left
                                }
                                horizontalAlignment: Text.AlignLeft
                            }

                            Text {
                                id: repository
                                text: "repository:  " + nameRepo
                                font {
                                    pixelSize: 12
                                    italic: true
                                }
                                anchors {
                                    right: parent.right
                                    left: parent.left
                                }

                                horizontalAlignment: Text.AlignLeft
                            }


                            RowLayout
                            {
                                anchors.right: parent.right
                                spacing: 20
                                Button {
                                    text: "Skip"
                                    onClicked:
                                    {
                                        removeError();
                                    }
                                }
                                Button {
                                    text: "Correct"
                                    onClicked:
                                    {
//                                        removeError();
                                    }
                                }


                            }
                        }
                    }
            }

        }// end ScrollView
    }
}
