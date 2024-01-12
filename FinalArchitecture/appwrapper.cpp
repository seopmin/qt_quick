#include <QNetworkRequest>
#include <QQmlContext>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include "appwrapper.h"

AppWrapper::AppWrapper(QGuiApplication *app, QObject *parent)
    : app(app)
    , QObject(parent)
{
    const QUrl url(u"qrc:/FinalArchitecture/Main.qml"_qs);
    QObject::connect(&mEngine, &QQmlApplicationEngine::objectCreationFailed,
        app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    DataSource *ds = new DataSource(this);
    mJokeModel.setDatasource(ds);

    mEngine.rootContext()->setContextProperty("myModel", &mJokeModel);
    mEngine.rootContext()->setContextProperty("myDatasource", ds);



    mEngine.load(url);
}
