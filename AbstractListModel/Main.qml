import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    visible: true
    width: 400
    height: 600
    minimumWidth: 400
    minimumHeight: 600
    title: qsTr("Hello World")


    ColumnLayout{
        anchors.fill: parent
        ListView{
            id : mListView
            Layout.fillWidth: true
            Layout.fillHeight: true

            model : myModel
            delegate: Rectangle {
                id: container
                height: 90
                radius: 10
                color : "gray"// Can also do modelData.favoriteColor directly but adding model makes it clear where the data is coming from. More readable
                border.color: "cyan"
                width: mListView.width
                RowLayout{
                    anchors.fill: parent
                    anchors.margins: 20

                    TextField{
                        text : names
                        Layout.fillWidth: true
                        onEditingFinished: {
                            console.log("Editing finished, new text is :"+ text + " at index :" + index)
                            model.names = text //The roles here are defined in model class
                        }
                    }

                    SpinBox{
                        id : mSpinbox
                        editable: true
                        Layout.fillWidth: true
                        onValueChanged: {
                            model.age = value;
                        }
                        Component.onCompleted: {
                            mSpinbox.value = model.age
                        }
                    }
                    Rectangle{
                        id: colorContainer
                        width : 50
                        height: 50
                        color: {
                            console.log("return", model.favoriteColor);
                            return model.favoriteColor
                        }
                        MouseArea{
                            anchors.fill: parent
                            ColorDialog{
                                id: colorDialog
                                title: "Please choose a color"
                                onAccepted: {
                                    // *** accepted의 매개변수 color 데이터에 문제가 있음. ColorDialog 내부적인 문제같음.
                                    console.log("You chose: " + color)
                                    colorContainer.color = color
                                    model.favoriteColor = color
                                }
                                onRejected: {
                                    console.log("Canceled")
                                }
                            }

                            onClicked: {
                                colorDialog.open()

                            }
                        }
                    }
                }
            }
        }

        RowLayout{
            width : parent.width

            Button{
                Layout.fillWidth: true
                height: 50
                text : "Add Person";
                onClicked: {
                    input.openDialog()
                }
                InputDialog{
                    id : input
                    onInputDialogAccepted: {
                        console.log("Here in main, dialog accepted");
                        console.log( " names : " + personNames + " age :" + personAge)
                        myModel.addPerson(personNames,personAge)
                    }
                }
//                contentItem: Text {
//                    text: parent.text
//                    color: "black"
//                }
            }
            Button{
                Layout.fillWidth: true
                height: 50
                text : "Remove Last";
                onClicked: {
                    myModel.removeLastPerson()
                    console.log("remove")
                }
            }
        }
    }

}
