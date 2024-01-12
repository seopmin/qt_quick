#include "jokemodel.h"

JokeModel::JokeModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int JokeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_datasource->dataItems().size();
}

QVariant JokeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_datasource->dataItems().size())
        return QVariant();

    Joke *joke = m_datasource->dataItems().at(index.row());
    if(role == JokeDataRole) {
        return joke->joke();
    }
    return QVariant();
}

bool JokeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Joke *joke = m_datasource->dataItems().at(index.row());
    bool somethingChanged = false;

    switch (role) {
        case JokeDataRole:
        if  (joke->joke() != value.toString()) {
            joke->setJoke(value.toString());
        }   somethingChanged = true;
    }

    if (somethingChanged) {
        emit dataChanged(index, index, QVector<int> () << role);
        return true;
    }
    return false;
}

Qt::ItemFlags JokeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> JokeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[JokeDataRole] = "joke";
    return roles;
}

DataSource *JokeModel::datasource() const
{
    return m_datasource;
}

void JokeModel::setDatasource(DataSource *newDatasource)
{
    beginResetModel();

    if (m_datasource && signalsConnected)
        m_datasource->disconnect(this);

    if (m_datasource == newDatasource)
        return;
    m_datasource = newDatasource;

    connect(m_datasource, &DataSource::preItemAdded, this, [=]() {
        const int index = m_datasource->dataItems().size();
        beginInsertRows(QModelIndex(), index, index);
    });
    connect(m_datasource, &DataSource::postItemAdded, this, [=]() {
        endInsertRows();
    });
    connect(m_datasource, &DataSource::preItemRemoved, this, [=](int index) {
        beginRemoveRows(QModelIndex(), index, index);
    });
    connect(m_datasource, &DataSource::postItemRemoved, this, [=]() {
        endRemoveRows();
    });


    endResetModel();
//    emit datasourceChanged();
}
