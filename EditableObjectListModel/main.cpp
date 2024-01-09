#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "objectlistwrapper.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ObjectListWrapper wrapper(&app);

    wrapper.initialize();
    /*
    const QUrl url(u"qrc:/EditableObjectListModel/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    */


    return app.exec();
}
