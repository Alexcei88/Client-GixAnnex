import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "../propertyFile"

ReviewData {
    id: viewData

    anchors.fill: parent

    // нужно создавать список, и динамически создавать
    PropertyValue {
        nameOption: "Host name:"
        widthFieldOption: viewData.column.widthFieldOption
        height: viewData.column.baseHeight
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "User name:"
        widthFieldOption: viewData.column.widthFieldOption
        height: viewData.column.baseHeight
        focus: true
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "Directory:"
        widthFieldOption: viewData.column.widthFieldOption
        height: viewData.column.baseHeight
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "Port:"
        widthFieldOption: column.widthFieldOption
        height: column.baseHeight
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
    PropertyValue {
        nameOption: "Destinition URL:"
        widthFieldOption: column.widthFieldOption
        height: column.baseHeight
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
    PropertyValue {
        nameOption: "Name:"
        widthFieldOption: column.widthFieldOption
        height: column.baseHeight
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
}

