# Editable ObjectListModel Qproperty

### Q_PROPERTY 등록

```cpp
Q_PROPERTY(QList<QObject*> mypersons READ mypersons WRITE setMypersons NOTIFY mypersonsChanged FINAL)
```

### Active signal in Model

```cpp
void Person::setNames(const QString &newNames)
{
    if (m_names == newNames)
        return;
    m_names = newNames;
    emit namesChanged();  // here
}
```

### Register model in QML

```cpp
model: Wrapper.mypersons
```

### Change using data from ModelData

```cpp
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
//                    text: names
                    text: modelData.names  // here
                    Layout.fillWidth: true
                    onEditingFinished: {
                        Wrapper.setNames(index, text);
                    }
                }
                SpinBox {
                    editable: true
//                    value: age
                    value: modelData.age  // here
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
//                    color: favoriteColor
                    color: modelData.favoriteColor  // here
                }
            }
        }
```