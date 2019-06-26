#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include "itemcanvas.h"
#include "scope_timer.h"

int main(int argc, char *argv[])
{
    {
        scope_timer s;
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        if(QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf") != -1){
            QFontDatabase::addApplicationFont(":/fonts/Roboto-Light.ttf");
            QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");
            QFont robotoFont;
            robotoFont.setFamily("Roboto");
            app.setFont(robotoFont);
        }
        else qInfo() << "Fonts not loaded from file-path provided";

        qmlRegisterType<ItemCanvas>("ctrls", 1, 0, "ItemCanvas");

        QQmlApplicationEngine engine;

//        QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;

        return app.exec();
    }
}
