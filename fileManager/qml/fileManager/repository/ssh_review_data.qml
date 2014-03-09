import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "../propertyFile"

ReviewData {
    id: viewData

    // нужно создавать список, и динамически создавать
    PropertyValue {
        nameOption: "Host name:"
        widthFieldOption: viewData.column.widthFieldOption
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "User name:"
        widthFieldOption: viewData.column.widthFieldOption
        focus: true
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "Directory:"
        widthFieldOption: viewData.column.widthFieldOption
        sizeFont: viewData.column.sizeFont
        anchors.left: viewData.column.left
    }
    PropertyValue {
        nameOption: "Port:"
        widthFieldOption: column.widthFieldOption
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
    PropertyValue {
        nameOption: "Destinition URL:"
        widthFieldOption: column.widthFieldOption
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
    PropertyValue {
        nameOption: "Name:"
        widthFieldOption: column.widthFieldOption
        sizeFont: column.sizeFont
        anchors.left: column.left
    }
}

