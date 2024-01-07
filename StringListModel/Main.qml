import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("StringList Model Demo")

    ListView {
        id: mListView
        anchors.fill: parent

        model: continentModel  // rootContext에 등록한 property
        delegate: Rectangle {
            height: 50
            radius: 10
            color: "dodgerblue"
            border.color: "cyan"
            width: parent.width
            Text {
                text: modelData   // model Data
                font.pointSize: 20
                anchors.centerIn: parent
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
