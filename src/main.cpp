#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "messagehandler.h"
#include "panomaximageprovider.h"

int main(int argc, char* argv[])
{
  qInstallMessageHandler(wsgui::messageHandler);
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreationFailed,
      &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);

  auto panomaxProvider = new wsgui::panomax::PanomaxImageProvider;
  engine.addImageProvider("panomax", panomaxProvider);

  engine.loadFromModule("WeatherstationGui", "Main");

  return app.exec();
}
