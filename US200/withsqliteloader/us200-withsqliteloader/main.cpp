#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databuilder.h"
#include "navigationmodel.h"
#include "dbinitializer.h"

//#define DATA_CREATION_MODE ;

int main(int argc, char *argv[])
{
#ifdef DATA_CREATION_MODE
    {
    DataBuilder builder;
    return builder.build();
    }
#else
    {
        DBInitializer dbInitializer;
        dbInitializer.initializeDBCache();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();

    NavigationModel navigationModel;
    context->setContextProperty("navigationModel", &navigationModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
    }
#endif
}
