#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "scope_timer.h"
#include "navmodel.h"

int main(int argc, char *argv[])
{    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    static scope_timer s;
    s.Reset("init");

    NavModel navModel;
    context->setContextProperty("navModel", &navModel);

    QObject::connect(&navModel, &NavModel::onAppLoaded,
                     [s](){
        s.Dispose();
    });

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
