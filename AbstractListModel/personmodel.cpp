#include "personmodel.h"

PersonModel::PersonModel(QObject *parent)
    : QAbstractListModel{parent}
{
    addPerson(new Person("Jamie Lannister", "red", 33));
    addPerson(new Person("Marry Lane", "cyan", 26));
    addPerson(new Person("Victor Trunk", "dodgerblue", 30));
    addPerson(new Person("Ariel Geeny", "blue", 33));
    addPerson(new Person("Knut Vikran", "lightblue", 26));
}

int PersonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)  // unusedParameter to avoid warning
    return mPersons.size();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mPersons.count())
        return QVariant();

    // the index is valid
    Person *person = mPersons[index.row()];
    if (role == NamesRole)
        return person->names();
    if (role == FavoriteColorRole)
        return person->favoriteColor();
    if (role == AgeRole)
        return person->age();

    return QVariant();
}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << Q_FUNC_INFO;
    Person *person = mPersons[index.row()];
    bool somethingChanged = false;

    switch (role) {
    case NamesRole:
    {
        if (person->names() != value.toString()) {
            qDebug() << "Changing names for " << person->names() << "to" << value.toString();
            person->setNames(value.toString());
            somethingChanged = true;
        }
    }
        break;
    case FavoriteColorRole:
    {
        if (person->favoriteColor() != value.toString()) {
            qDebug() << "Changing color for " << person->names();
            person->setFavoriteColor(value.toString());
            somethingChanged = true;
        }
    }
        break;
    case AgeRole:
    {
        if (person->age() != value.toInt()) {
            qDebug() << "Changing age for " << person->names();
            person->setAge(value.toInt());
            somethingChanged = true;
        }
    }
    }

    if (somethingChanged) {
        qDebug() << "good";

        emit dataChanged(index, index, QVector<int>() << role);

        return true;
    }
    return false;
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    qDebug() << Q_FUNC_INFO;
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PersonModel::roleNames() const
{
    qDebug() << Q_FUNC_INFO;
    // connect hash
    QHash<int, QByteArray> roles;
    roles[NamesRole] = "names";
    roles[FavoriteColorRole] = "favoriteColor";
    roles[AgeRole] = "age";
    return roles;
}

void PersonModel::addPerson(Person *person)
{
    /*
        modelList에 추가하려면 beginInsertRows와 endInsertRows 메서드를 꼭 추가해야함.
    */
    const int index = mPersons.size();
    beginInsertRows(QModelIndex(), index, index);
    mPersons.append(person);
    endInsertRows();
}

void PersonModel::addPerson()
{
    Person *person = new Person("Added Person", "yellowgreen", 45, this);
    addPerson(person);
}

void PersonModel::addPerson(const QString &names, const int &age)
{
    Person *person = new Person("Added Person", "yellowgreen", 45, this);
    addPerson(person);
}

void PersonModel::removePerson(int index)
{
    /*
        제거할 때도 마찬가지로
        beginRemoveRows & endRemoveRows 메서드 사용
    */
    beginRemoveRows(QModelIndex(), index, index);
    mPersons.removeAt(index);
    endRemoveRows();
}

void PersonModel::removeLastPerson()
{
    removePerson(mPersons.size()-1);
}
