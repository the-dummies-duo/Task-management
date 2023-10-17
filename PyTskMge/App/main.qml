import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "Task management project"


    menuBar: MenuBar {
        objectName: "MenuBar"
        Menu {
            title: qsTr("&Tasks")
            Action { text: qsTr("&New...") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&View")
            Action { text: qsTr("&View all tasks") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&Our GitHub") }
        }
    }
}