#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "panomaximageprovider.h"
#include "panomaximages.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto imageProvider = new wsgui::panomax::PanomaxImageProvider;
    wsgui::panomax::PanomaxImages::setPanomaxImageProvider(imageProvider);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.addImageProvider(wsgui::panomax::PanomaxImageProvider::providerId, imageProvider);
    engine.loadFromModule("WeatherstationGui", "Main");

    return app.exec();
}
