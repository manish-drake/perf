import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: qsTr("us100")
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1{
        }
        Page2{
        }
        Page3{
        }
        Page4{
        }
    }


    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("No controls")
        }
        TabButton {
            text: qsTr("n-number controls")
        }
        TabButton{
            text: qsTr("with loader")
        }
        TabButton{
            text: qsTr("with canvas item")
        }       
    }
}
