import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    title: qsTr("us200")
    Loader{
        id:loader
        anchors.fill: parent
        source:"Page1.qml"
        onSourceChanged: {
            navModel.scopeDispose()
        }
    }
    Component.onCompleted: {
        navModel.appLoaded()
    }
}
