import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Object List Model Demo")


    ListView {
        id: mListView
        anchors.fill: parent

        model: personModel

        delegate: Rectangle {
            height: 90
            radius: 10
            color: "gray"
            border.color: "cyan"
            width: parent.width
            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                TextField {
                    text: names
                    Layout.fillWidth: true
                }
                SpinBox {
                    editable: true
                    value: age
                    Layout.fillWidth: true
                }
                Rectangle {
                    width: 50
                    height: 50
                    color: favoriteColor
                }
            }
        }
    }
}
