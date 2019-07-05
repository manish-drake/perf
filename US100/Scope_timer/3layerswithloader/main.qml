import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("N-controls using loader with 3 layers")
    Component{ModalPage1{}}
    Component{ModalPage2{}}
    Page1{}
    Loader{
        id: modalLoader1
        anchors.fill: parent
        onSourceChanged: navModel.scopeDispose()
    }
    Loader{
        id: modalLoader2
        anchors.fill: parent
        onSourceChanged: navModel.scopeDispose()
    }
    Component.onCompleted: {
        navModel.appLoaded()
    }
}
