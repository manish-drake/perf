import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    anchors.fill:parent
    anchors.topMargin: 35
    Rectangle{
        anchors.centerIn: parent
        height: 100; width: 250
        color: mArea.pressed ? "red" : "yellow"
        Text{
            anchors.centerIn: parent
            font.pixelSize: 28
            text:"Click"
        }
        MouseArea{
            id: mArea
            anchors.fill: parent
            onClicked: {
                navModel.scopeDispose()
                console.log("--------------------------------------------------------------------------------------------button clicked")
            }
        }
    }
}


