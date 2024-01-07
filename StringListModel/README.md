# String List Model From C++

### Main.cpp file

```cpp
/* main.cpp - string list 생성 */
QStringList continentList;
continentList.append("Africa");
continentList.append("Europ");
continentList.append("America");
continentList.append("Asia");
continentList.append("Oceania");
continentList.append("Antarctica");

/* property 등록 */
engine.rootContext()->setContextProperty("continentModel", continentList);
```

### QML file

: get data from “modelData”

```dart
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
            text: modelData   // get model Data
            font.pointSize: 20
            anchors.centerIn: parent
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
```