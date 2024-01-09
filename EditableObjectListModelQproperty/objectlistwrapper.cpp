#include "objectlistwrapper.h"
#include <QDebug>

ObjectListWrapper::ObjectListWrapper(QObject *parent)
    : QObject{parent}
{

}

ObjectListWrapper::ObjectListWrapper(QGuiApplication *app, QObject *parent) : QObject{parent}, mApp(app)
{
    populateModelWithData();
}

void ObjectListWrapper::initialize()
{
    resetModel();

    const QUrl url(u"qrc:/EditableObjectListModelQproperty/Main.qml"_qs);

    QObject::connect(&mEngine, &QQmlApplicationEngine::objectCreationFailed,
        mApp, []() {

            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    mEngine.load(url);
}

void ObjectListWrapper::setNames(int index, const QString &names)
{
    qDebug() << "Changing name: " << names;
    if (index >= mPersons.size())
        return;

    Person *person = static_cast<Person*>(mPersons.at(index));
    if (names!=person->names()) {
        person->setNames(names);
//        resetModel();
    }
    printPerson();
}

void ObjectListWrapper::setAge(int index, const int &age)
{
    if (index >= mPersons.size())
        return;

    Person *person = static_cast<Person *> (mPersons.at(index));
    if (age!=person->age()) {
        person->setAge(age);
//        resetModel();
    }
    printPerson();
}

void ObjectListWrapper::setFavoriteColor(int index, const QString &favoriteColor)
{
    if (index >= mPersons.size())
        return;

    Person *person = static_cast<Person *> (mPersons.at(index));
    if (favoriteColor != person->favoriteColor()) {
        person->setFavoriteColor(favoriteColor);
//        resetModel();
    }
    printPerson();
}

QList<QObject *> ObjectListWrapper::persons() const
{
    return mPersons;
}

void ObjectListWrapper::addPerson()
{
    mPersons.append(new Person("New Person", "green", 32, this));
//    resetModel();
    emit mypersonsChanged();
}

void ObjectListWrapper::populateModelWithData()
{
    mPersons.append(new Person("John Doe", "green", 32, this));
    mPersons.append(new Person("Mary Green", "blue", 23, this));
    mPersons.append(new Person("Mithch Natson", "dodgerblue", 30, this));
}

void ObjectListWrapper::resetModel()
{
    mEngine.rootContext()->setContextProperty("Wrapper", this);
//    mEngine.rootContext()->setContextProperty("myModel", QVariant::fromValue(persons()));
}

void ObjectListWrapper::printPerson()
{
    qDebug() << "---------Persons----------";
    foreach (QObject *obj, mPersons) {
        Person *person = static_cast<Person *> (obj);
        qDebug() << person->names() << " " << person->age() << " " << person->favoriteColor();
    }
}

QList<QObject *> ObjectListWrapper::mypersons() const
{
    return mPersons;
}

void ObjectListWrapper::setMypersons(const QList<QObject *> &newMypersons)
{
    if (mPersons == newMypersons)
        return;
    mPersons = newMypersons;
    emit mypersonsChanged();
}
