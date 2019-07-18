import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us200")
    Component{Page1{}}
    Component{Page2{}}
    Component{Page3{}}
    Component{Page4{}}
    Component{Page5{}}
    StackView{
        id: stack
        anchors.fill: parent
        initialItem: "qrc:/Page1.qml"
        onCurrentItemChanged: {
            navModel.scopeDispose()
        }
    }
    Component.onCompleted: {
        navModel.appLoaded()
    }
}

