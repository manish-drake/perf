#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include "scope_timer.h"
#include "navmodel.h"
#include <QSGRendererInterface>
#include <QQuickWindow>
#include <touchy.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    touchy t;

    if(QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf") != -1){
        QFontDatabase::addApplicationFont(":/fonts/Roboto-Light.ttf");
        QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");
        QFont robotoFont;
        robotoFont.setFamily("Roboto");
        app.setFont(robotoFont);
    }
    else qInfo() << "Fonts not loaded from file-path provided";

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    NavModel navModel;
    context->setContextProperty("navModel", &navModel);

    static scope_timer s;
    QObject::connect(&navModel, &NavModel::onAppLoaded,
                     [s](){
        s.Dispose();
    });

    s.Reset("init");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
