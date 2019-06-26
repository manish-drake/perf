import QtQuick 2.7
import QtQuick.Layouts 1.3

Item{
    anchors.fill: parent
    Text{text:"Page5"; font.bold: true; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter}
    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.topMargin: 50
        rowSpacing: 10
        columnSpacing: 10
        Text { Layout.column: 0; Layout.row:0; Layout.alignment: Qt.AlignHCenter; text: "One"}
        Text { Layout.column: 1; Layout.row:0; Layout.alignment: Qt.AlignHCenter; text: "Two"}
        Text { Layout.column: 0; Layout.row:1; Layout.alignment: Qt.AlignHCenter; text: "Three"}
        Text { Layout.column: 1; Layout.row:1; Layout.alignment: Qt.AlignHCenter; text: "Four"}
        Text { Layout.column: 0; Layout.row:2; Layout.alignment: Qt.AlignHCenter; text: "Five"}
        Text { Layout.column: 1; Layout.row:2; Layout.alignment: Qt.AlignHCenter; text: "Six"}
        Text { Layout.column: 0; Layout.row:3; Layout.alignment: Qt.AlignHCenter; text: "Seven"}
        Text { Layout.column: 1; Layout.row:3; Layout.alignment: Qt.AlignHCenter; text: "Eight"}
        Text { Layout.column: 0; Layout.row:4; Layout.alignment: Qt.AlignHCenter; text: "Nine"}
        Text { Layout.column: 1; Layout.row:4; Layout.alignment: Qt.AlignHCenter; text: "Ten"}
        Text { Layout.column: 0; Layout.row:5; Layout.alignment: Qt.AlignHCenter; text: "One"}
        Text { Layout.column: 1; Layout.row:5; Layout.alignment: Qt.AlignHCenter; text: "Two"}
        Text { Layout.column: 0; Layout.row:6; Layout.alignment: Qt.AlignHCenter; text: "Three"}
        Text { Layout.column: 1; Layout.row:6; Layout.alignment: Qt.AlignHCenter; text: "Four"}

        Rectangle{
            id:frame4
            width:100
            height: 100
            radius: 50
            color: "lightgreen"
            Layout.column: 0; Layout.row:7; Layout.alignment: Qt.AlignHCenter;
            Image {
                anchors.centerIn: parent
                width: 50; height: 50
                fillMode: Image.PreserveAspectFit
                source: "img/left-arrow_light.png"
            }
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    navModel.reset("prev");
                    loader.setSource("Page4.qml")
                }
            }
        }
        Rectangle{
            id:frame5
            width: 100
            height: 100
            radius: 50
            color: "lightgreen"
            Layout.column: 1; Layout.row:7; Layout.alignment: Qt.AlignHCenter;
            Image {
                anchors.centerIn: parent
                width: 50; height: 50
                fillMode: Image.PreserveAspectFit
                source: "img/right-arrow_light.png"
            }
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    navModel.reset("next");
                    loader.setSource("Page1.qml")
                }
            }
        }
    }
}
