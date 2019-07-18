import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us200")
    Component{Page2{}}
    Component{Page3{}}
    Component{Page4{}}
    Component{Page5{}}
    Loader{
        id:loader
        anchors.fill: parent
        source: "Page1.qml"
        onSourceChanged: {
            navModel.scopeDispose()
        }
    }
    Component.onCompleted: {
        navModel.appLoaded()
    }
}

