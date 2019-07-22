import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us200")    
    StackView{
        id: stack
        anchors.fill: parent
        initialItem: "qrc:/Page1.qml"
        onCurrentItemChanged: {
            navModel.scopeDispose()
        }
    }
}

