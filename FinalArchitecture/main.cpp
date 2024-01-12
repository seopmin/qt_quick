#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appwrapper.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppWrapper wrapper(&app);

//    QQmlApplicationEngine engine;
//    const QUrl url(u"qrc:/FinalArchitecture/Main.qml"_qs);
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
//        &app, []() { QCoreApplication::exit(-1); },
//        Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
