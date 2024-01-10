#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "personmodel.h"
#include "datasource.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    PersonModel mModel;
    DataSource * ds = new DataSource(&mModel);
    mModel.setDataSource(ds);

    engine.rootContext()->setContextProperty("myModel",&mModel);
    engine.rootContext()->setContextProperty("myDataSource",ds);


    const QUrl url(u"qrc:/ExternalDataSource/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
