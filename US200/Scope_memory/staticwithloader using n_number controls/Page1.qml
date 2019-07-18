import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    anchors.fill:parent
    anchors.topMargin: 35
    Text{id:p1;text:"Page1"; font.bold: true; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter}
    ColumnLayout{
        id:cols
        anchors.fill:parent
        anchors{top:parent.top; topMargin: 30; margins: 5}
        spacing: 0
        Text{
            id:abc
            text:"n_controls with staztic data navigation"}
        Rectangle{
            id:frame
            Layout.fillWidth: true
            height: 25
            border.color: "gray"
            border.width: 1
            TextInput{
                id: txtPlain
                anchors.fill:parent
                anchors.margins: 4
            }
        }
        Rectangle{
            id:frame2
            width:200
            height:60
            color: "lightgreen"
            Text{
                anchors.centerIn: parent
                text:"Submit"}
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    console.log("button clicked")
                }
            }
        }
        Image {
            width: 130; height: 100
            fillMode: Image.PreserveAspectFit
            source: "img/qtlogo.png"
        }
        RowLayout{
            Text{
                id:abc1
                text:"Text"
            }
            Text{
                id:abc2
                text:slider.value
            }
            Slider {
                id:slider
                maximumValue: 5.0
                stepSize: 1.0
            }
        }
        RowLayout {
            ExclusiveGroup { id: group1 }
            RadioButton {
                checked: true
                text: qsTr("First")
                exclusiveGroup: group1
            }
            RadioButton {
                text: qsTr("Second")
                exclusiveGroup: group1
            }
            RadioButton {
                text: qsTr("Third")
                exclusiveGroup: group1
            }
        }
        RowLayout {
            ExclusiveGroup { id: group }
            RadioButton {
                checked: true
                text: qsTr("1")
                exclusiveGroup: group
            }
            RadioButton {
                text: qsTr("2")
                exclusiveGroup: group
            }
            RadioButton {
                text: qsTr("3")
                exclusiveGroup: group
            }
        }
        RowLayout {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 70
            anchors.horizontalCenter: parent.horizontalCenter
            Rectangle{
                id:frame4
                width:100
                height: 100
                radius: 50
                color: "lightgreen"
               Layout.alignment: Qt.AlignHCenter
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
                        loader.setSource("Page5.qml")
                    }
                }
            }
            Rectangle{
                id:frm5
                width: 100
                height: 100
                radius: 50
                color: "lightgreen"
                Layout.alignment: Qt.AlignHCenter
                Image {
                    anchors.centerIn: parent
                    width: 50; height: 50
                    fillMode: Image.PreserveAspectFit
                    source: "img/right-arrow_light.png"
                }
                MouseArea{
                    anchors.fill:parent
                    onClicked:{
                        navModel.reset("next");
                        loader.setSource("Page2.qml")
                    }
                }
            }
        }
    }
}


