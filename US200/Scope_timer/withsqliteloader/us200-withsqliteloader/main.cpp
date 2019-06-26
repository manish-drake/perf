#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include "databuilder.h"
#include "navigationmodel.h"
#include "dbinitializer.h"
#include "scope_timer.h"
#include "scope_memself.h"

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
        static scope_timer s;
        s.Reset("init");
        DBInitializer dbInitializer;
        dbInitializer.initializeDBCache();

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

        QQmlApplicationEngine engine;
        QQmlContext *context = engine.rootContext();
        NavigationModel navigationModel;
        context->setContextProperty("navigationModel", &navigationModel);

        QObject::connect(&navigationModel, &NavigationModel::onAppLoaded,
                         [s](){
            s.Dispose();
        });

        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;

        return app.exec();
    }
#endif
}
