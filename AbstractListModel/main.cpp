#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "personmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PersonModel mModel;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("myModel", &mModel);


    const QUrl url(u"qrc:/AbstractListModel/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
