# ObjectListModel

### Model cpp file

> save as `Q_PROPERTY`
> 

```dart
Q_PROPERTY(QString names READ names WRITE setNames NOTIFY namesChanged FINAL)
Q_PROPERTY(QString favoriteColor READ favoriteColor WRITE setFavoriteColor NOTIFY favoriteColorChanged FINAL)
Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged FINAL)
```

### main.cpp file

> 1.  make Model List
2. register model list in rootContext
> 

```dart
QList<QObject *> personList;
personList.append(new Person("John Doe C++", "green", 32, &engine));
personList.append(new Person("Mary Green", "blue", 23, &engine));
personList.append(new Person("Mitch Nathson", "dodgerblue", 30, &engine));
personList.append(new Person("Daniel sten", "red", 67, &engine));

engine.rootContext()->setContextProperty("personModel", QVariant::fromValue(personList));
```

### QML file

> match “model” & “the data in model list registered”
> 

```dart
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
```