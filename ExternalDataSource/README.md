# ExternalDataSource

## It is dividing data source and **general functions** from Model file

> [나의 한줄] 
굳이 이렇게…? 할 필요가 있나? data edit, get도 Model에서 할거면 그냥 둘이 합치는 게 더 직관적일 듯
> 

![Untitled](ExternalDataSource%20dad6561f14d04c79b9c685a416e172cc/Untitled.png)

### In datasource file

> For use begin method.
> 

```cpp
signals:
    void prePersonAdded();
    void postPersonAdded();
    void prePersonRemoved(int index);
    void postPersonRemoved();

/* example for using */
void DataSource::addPerson(Person *person)
{
    emit prePersonAdded();  // here
    mPersons.append(person);
    emit postPersonAdded();  // here
}
```

> Create data source
> 

```cpp
private :
    QList<Person*> mPersons;
```

### In Model file

> Create data source
> 

```cpp
private :
    DataSource * m_dataSource;
    bool m_signalConnected;
```

> Connect to data source’s signals
> 

```cpp
void PersonModel::setDataSource(DataSource *dataSource)
{
    /*
        when model data is changed
        - beginResetModel()
        - endResetModel()
    */

    beginResetModel();  

    if( m_dataSource && m_signalConnected)
        m_dataSource->disconnect(this);

    m_dataSource = dataSource;

    connect(m_dataSource,&DataSource::prePersonAdded,this,[=](){
        const int index = m_dataSource->dataItems().size();
        beginInsertRows(QModelIndex(),index,index);
    });

    connect(m_dataSource,&DataSource::postPersonAdded,this,[=](){
        endInsertRows();
    });

    connect(m_dataSource,&DataSource::prePersonRemoved,this,[=](int index){
       beginRemoveRows(QModelIndex(), index, index);
    });

    connect(m_dataSource,&DataSource::postPersonRemoved,this,[=](){
       endRemoveRows();
    });

    m_signalConnected = true;

    endResetModel();

}
```

### In main.cpp file

```cpp
QQmlApplicationEngine engine;

PersonModel mModel;
DataSource * ds = new DataSource(&mModel);
mModel.setDataSource(ds);

engine.rootContext()->setContextProperty("myModel",&mModel);
engine.rootContext()->setContextProperty("myDataSource",ds);
```