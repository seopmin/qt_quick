#ifndef JOKE_H
#define JOKE_H

#include <QObject>

class Joke : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString joke READ joke WRITE setJoke NOTIFY jokeChanged FINAL)
public:
    explicit Joke(const QString &s, QObject *parent = nullptr);

    QString joke() const;
    void setJoke(const QString &newJoke);

signals:
    void jokeChanged();

private:
    QString m_joke;
};

#endif // JOKE_H
