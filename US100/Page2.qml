import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    Layout.fillHeight: true; Layout.fillWidth: true
    Column{
        id:cols
        anchors.fill:parent
        anchors.margins: 5
        spacing: 3
        Text{
            id:abc
            text:"abc"}
        Rectangle{
            id:frame
            width:parent.width
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
            height: 25
            color: "lightgreen"
            Text{
                anchors.centerIn: parent
                text:"Submit"}
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    console.log("button clicked")
                    abc.text= txtPlain.text
                }
            }
        }
        Image {
            width: 130; height: 100
            fillMode: Image.PreserveAspectFit
            source: "img/qtlogo.png"
        }
        RowLayout{
            Rectangle{
                id:frame4
                width:100
                height: 100
                radius: 50
                color: "lightgreen"
                Image {
                    anchors.centerIn: parent
                    width: 50; height: 50
                    fillMode: Image.PreserveAspectFit
                    source: "img/left-arrow_light.png"
                }
                MouseArea{
                    anchors.fill:parent
                    onClicked: console.log("prev clicked")
                }
            }
            Rectangle{
                id:frame5
                width:100
                height: 100
                radius: 50
                color: "lightgreen"
                Image {
                    anchors.centerIn: parent
                    width: 50; height: 50
                    fillMode: Image.PreserveAspectFit
                    source: "img/right-arrow_light.png"
                }
                MouseArea{
                    anchors.fill:parent
                    onClicked: console.log("next clicked")
                }
            }
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
    }
}

