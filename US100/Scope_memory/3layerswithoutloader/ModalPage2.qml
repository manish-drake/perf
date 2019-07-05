import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    color:"#2A000000"
    MouseArea{anchors.fill: parent}
    RowLayout{
        anchors.fill: parent
        Rectangle{
            Layout.fillWidth: true; Layout.maximumWidth: 650; Layout.alignment: Qt.AlignCenter; Layout.margins: 15
            height: 300
            Layout.maximumHeight: parent.height - 20
            radius: 4
            color: "#FFFFFF"
            ColumnLayout{
                id: content
                anchors{fill: parent; topMargin: 10; bottomMargin: 20}
                spacing: 5
                Item{
                    anchors{top:parent.top;left:parent.left; right:parent.right}
                    Layout.bottomMargin: 12
                    height: 72
                    Text {
                        text:"Modal Page 2"
                        anchors{verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 100; right: parent.right; rightMargin: 100}
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                    }
                    Item{
                        id: headerBtn
                        anchors{top: parent.top; bottom: parent.bottom}
                        width: 90
//                        MouseArea {
//                            id: mouseArea
//                            anchors.fill: parent
//                            onClicked: modalLoader2.setSource("")
//                        }
                        Image{
                                anchors.centerIn: parent
                                source: "qrc:/img/close.png"
                                asynchronous: true
                            }
                    }
                }
                Image {id:img
                    width: 130; height: 100
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: "img/qtlogo.png"
                }
                Rectangle{
                    id:frame2
                    width:200
                    height:60
                    color: "lightgreen"
                    radius:5
                    anchors{right:parent.right; bottom:parent.bottom; rightMargin: 20}
                    Text{
                        anchors.centerIn: parent
                        text:"close"
                    }
//                    MouseArea{
//                        anchors.fill:parent
//                        onClicked: modalLoader2.setSource("")
//                    }
                }

            }
        }
    }
}
