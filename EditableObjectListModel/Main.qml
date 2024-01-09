import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView {
        id: mListView
        anchors.fill: parent

        model: myModel

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
                    onEditingFinished: {
                        Wrapper.setNames(index, text);
                    }
                }
                SpinBox {
                    editable: true
                    value: age
                    Layout.fillWidth: true
                    onValueChanged: {
                        if (value === model.age) {

                        } else {
                            Wrapper.setAge(index, value);
                        }
                    }
                }
                Rectangle {
                    width: 50
                    height: 50
                    color: favoriteColor
                }
            }
        }
    }

    Rectangle {
        id: mButton
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        color: "green"
        Text {
            anchors.centerIn: parent
            text: "Add Person"
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                Wrapper.addPerson();
            }
        }
    }
}
