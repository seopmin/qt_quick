#ifndef APPWRAPPER_H
#define APPWRAPPER_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "datasource.h"
#include "jokemodel.h"

class AppWrapper : public QObject
{
    Q_OBJECT
public:
    explicit AppWrapper(QGuiApplication *app, QObject *parent = nullptr);

    bool initialize();

private:

    void resetModel () ;

    QQmlApplicationEngine mEngine;
    QGuiApplication *app;
    JokeModel mJokeModel;

};

#endif // APPWRAPPER_H
