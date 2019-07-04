import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("n-number-controls")
    Page1{}
    Component.onCompleted: {
        navModel.appLoaded()
    }
}
