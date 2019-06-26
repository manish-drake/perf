import QtQuick 2.7
import QtQuick.Controls 2.0
import ctrls 1.0

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("n-controls using canvas item")
    ItemCanvas{
        width: 480; height: 800
    }
    Component.onCompleted: {
             Qt.callLater(Qt.quit)
        }
}
