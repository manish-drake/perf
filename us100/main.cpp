#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "itemcanvas.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterType<ItemCanvas>("ctrls", 1, 0, "ItemCanvas");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
