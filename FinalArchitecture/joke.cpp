#include "joke.h"

Joke::Joke(const QString &s, QObject *parent)
    : m_joke(s)
    , QObject{parent}
{

}

QString Joke::joke() const
{
    return m_joke;
}

void Joke::setJoke(const QString &newJoke)
{
    if (m_joke == newJoke)
        return;
    m_joke = newJoke;
    emit jokeChanged();
}
