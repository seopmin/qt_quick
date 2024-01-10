# AbstractListModel

### Include & Inherit QAbstractListModel in Model class

```cpp
#include <QObject>
#include <QAbstractListModel>

class PersonModel : public QAbstractListModel  // here (no QObject)
{
    Q_OBJECT
public:
    explicit PersonModel(QObject *parent = nullptr);

signals:

};

PersonModel::PersonModel(QObject *parent)
    : QAbstractListModel{parent}  // here (no QObject)
{

}

```

### Required Overrides

> 모델이 정상적으로 작동하기 위해 꼭 구현해야 하는 기본 사항
These methods are meant to be called by the system, not me.
> 

```cpp
/* return number of items */
int rowCount(const QModelIndex &parent = QModelIndex()) const;

/* grab data from model */
QVariant data(const QModelIndex &index, int role) const;

/* Modify data in model */
bool setData(const QModelIndex &index, const QVariant &value, int role);

/* Control model behavior (let you know it can be edited or not) */
Qt::ItemFlags flags(const QModelIndex& index) const;

/* Make your roles usable in QML */
QHash<int, QByteArray> roleNames() const;
```

### Expose model in QML

> in main.cpp
> 

```cpp
engine.rootContext()->setContextProperty("myModel", &myModel);
```

### Using the C++ model in QML

```cpp
ListView{
    id : mListView
    Layout.fillWidth: true
    Layout.fillHeight: true

    model : myModel  // here
    delegate: Rectangle {
         ......
    }
}
```

### Read model role data and assign to qml elements

```cpp
delegate: Rectangle {
  height: 90
  radius: 10
  color : "gray"// Can also do modelData.favoriteColor directly but adding model makes it clear where the data is coming from. More readable
  border.color: "cyan"
  width: parent.width
  RowLayout{
      anchors.fill: parent
      anchors.margins: 20

      TextField{
          text : names
          Layout.fillWidth: true
          onEditingFinished: {
              console.log("Editing finished, new text is :"+ text + " at index :" + index)
              model.names = text //The roles here are defined in model class
              console.log(model);

          }
      }
.......
```

### TIP!!

> 자식 컴포넌트에서 부모 컴포넌트에 시그널 보내는 방법 in QML
> 

```cpp
/* 자식 컴포넌트 in InputDialog.qml */

signal inputDialogAccepted  // 시그널 등록

rootId.inputDialogAccepted()  // 시그널 호출
```

```cpp
/* 부모 컴포넌트 in main.qml */

InputDialog{
    id : input
    onInputDialogAccepted: {  // on시그널을 통해 받음
        console.log("Here in main, dialog accepted");
        console.log( " names : " + personNames + " age :" + personAge)
        myModel.addPerson(personNames,personAge)
    }
}
```