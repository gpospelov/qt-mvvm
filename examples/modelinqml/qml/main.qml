import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    width: 540
    height: 700
    visible: true

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "backEnd.particleViewModel()"
        }

        TableView {
            width: 300
            height: 150
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: backEnd.particleViewModel()

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: "lavender"
                border.width: 1

                Text {
                    text: model.display
                    anchors.centerIn: parent
                }
            }
        }

        Text {
            text: "backEnd.tableModel()"
        }

        TableView {
            width: 300
            height: 200
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: backEnd.tableModel()

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: "oldlace"
                border.width: 1

                TextInput {
                    anchors.centerIn: parent
                    text: model.display
                    onEditingFinished: model.edit = text
                }
            }
        }

        TableView {
            width: 300
            height: 200
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: backEnd.tableModel()

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: "oldlace"
                border.width: 1

                TextInput {
                    anchors.centerIn: parent
                    text: model.display
                    onEditingFinished: model.edit = text
                }
            }
        }

    }
}

