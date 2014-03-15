import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "../propertyFile"

Rectangle {

    function nextPage()
    {
        console.log("Page \"ssh_review_data\": Cloning repository into...");
        var nextpage = modelRepoXMLCommon.get(0).url_addrepo;
        console.log(nextpage);

        var destUrl = addRepository.getOptions("Destinition URL")
        var initText = "Cloning repository into <i>"+ destUrl + "</i>";

        if(nextpage !== "")
        {
            stackView.push({ item: Qt.resolvedUrl(nextpage), destroyOnPop: true,
                             properties: { initText: initText}
                           })
        }
        addRepository.startAddRepository();
    }

    function prevPage()
    {

    }

    function actualizeButton()
    {
        buttonNext.text = "Add"

        var array = addRepository.options;
        for(var i = 0; i < array.length; ++i)
        {
            modelReviewData.append({"_nameOption": array[i] + ":", "_valueOption" : ""});
        }

        // заполняем поля, если они были заполнены
        for(var k = 0; k < modelReviewData.count; ++k)
        {
            var key = modelReviewData.get(k)._nameOption.substring(0, modelReviewData.get(k)._nameOption.length - 1);
            var value = addRepository.getOptions(key);
            modelReviewData.get(k)._valueOption = value;
        }
    }
    ListModel {
        id: modelReviewData
    }

    SystemPalette { id: sysPal }
    color: sysPal.window

    Text {
        id: head
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 15

        text: "Adding a remote server using ssh"
        font {
            pixelSize: 16
            bold: true
        }
    }

    ListView {

        id: viewPreferences

        property int sizeFont: 12
        property int widthFieldOption: 100

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: head.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        spacing: 10

        model: modelReviewData

        delegate: PropertyValue
        {
            widthFieldOption: viewPreferences.widthFieldOption
            sizeFont: viewPreferences.sizeFont
            nameOption: _nameOption
            valueOption: _valueOption
            anchors.left: parent.left
        }
    }
}
