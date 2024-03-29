#ifndef JOKEMODEL_H
#define JOKEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "datasource.h"

class JokeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DataSource* datasource READ datasource WRITE setDatasource NOTIFY datasourceChanged FINAL)

    enum ModelRoles {
        JokeDataRole = Qt::UserRole + 1
    };

public:
    explicit JokeModel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QHash<int, QByteArray> roleNames() const;



    DataSource *datasource() const;
    void setDatasource(DataSource *newDatasource);

signals:

    void datasourceChanged();
private:
    DataSource *m_datasource = nullptr;
    bool signalsConnected {false};
};

#endif // JOKEMODEL_H
