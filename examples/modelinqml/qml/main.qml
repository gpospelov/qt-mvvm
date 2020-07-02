import QtQuick 2.12
import QtQuick.Controls 2.12
import TableModel 0.1

ApplicationWindow {
    width: 540
    height: 960
    visible: true

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {}

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            Text {
                text: display
            }
        }
    }
}

