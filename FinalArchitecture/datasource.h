#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkRequest>
#include <QQmlContext>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "joke.h"

#include <QDebug>

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    Q_INVOKABLE void fetchJokes(int number);

    void addJoke(Joke *joke);

    Q_INVOKABLE void addJoke();

    Q_INVOKABLE void addJoke(const QString & jokeParam);

    Q_INVOKABLE void removeJoke(int index);

    Q_INVOKABLE void removeLastJoke();

    QList<Joke *> dataItems();

signals:
    void preItemAdded();
    void postItemAdded();
    void preItemRemoved(int index);
    void postItemRemoved();

private slots:
    void dataReadyRead();
    void dataReadFinished();

private:
    QNetworkAccessManager * mNetManager;
    QNetworkReply * mNetReply;
    QByteArray * mDataBuffer;
//    QStringList mJokes;
    QList<Joke *> mJokes;
};

#endif // DATASOURCE_H
