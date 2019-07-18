import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    title: qsTr("us200")
    Item{
        anchors{top: parent.top; right: parent.right}
        height:90
        width: 90
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: Qt.quit()
        }
        Image{
            anchors.centerIn: parent
            source: "qrc:/img/close.png"
            asynchronous: true
        }
    }
    Loader{
        id:loader
        anchors.fill: parent
        source:"Page1.qml"
        onSourceChanged: {
            navModel.scopeDispose()
        }
    }
}

