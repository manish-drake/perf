import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us200")
    property string currPath
    Loader{
        id:loader
        anchors.fill: parent
        source: "Page1.qml"
        onSourceChanged: {
            navigationModel.scopeDispose()
        }
    }
    Component.onCompleted: {
        navigationModel.appLoaded()
    }
}

