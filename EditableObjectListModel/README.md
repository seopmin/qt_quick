# EditableObjectModelList

### Wrapper class(QObject)

> **Make constructor that can receive `QGuiApplication` type data**
> 

```cpp
ObjectListWrapper(QGuiApplication *app, QObject *parent = nullptr);

QQmlApplicationEngine mEngine;
QGuiApplication *mApp;
```

> **Make Object List ( you have to set a type “QObject*” )**
> 

```cpp
// This should be QObject*, Person* is not going to work in QML
QList<QObject*> mPersons;
```

> **********Initialize func**********
- This scope is the place that sets a engine load
- person func is returned “QObject list”
> 

```cpp
void ObjectListWrapper::initiallize()
{
		// for using model in QList
    mEngine.rootContext()->setContextProperty("myModel", QVariant::fromValue(persons()));
		// for using Wrapper's method
		mEngine.rootContext()->setContextProperty("Wrapper", this);
    
		const QUrl url(u"qrc:/EditableObjectListModel/Main.qml"_qs);

    QObject::connect(&mEngine, &QQmlApplicationEngine::objectCreationFailed,
        mApp, []() {

            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    mEngine.load(url);
}
```

> **The funcs that change the data we want. (macro Q_INVOKABLE)**
> 

```cpp
Q_INVOKABLE void setNames(int index, const QString &names);
Q_INVOKABLE void setAge(int index, const int &age);
Q_INVOKABLE void setFavoriteColor(int index, const QString &favoriteColor);
```