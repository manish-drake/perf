import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us100-using loader")
    Component{Page2{}}
    Loader{
        id: pageLoader
        source: "qrc:/Page2.qml"
    }
    Component.onCompleted: {
        navModel.appLoaded()
    }
}
