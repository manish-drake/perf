#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "scope_timer.h"

int main(int argc, char *argv[])
{
    {
        scope_timer s;
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;

//        QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;

        return app.exec();
    }
}
