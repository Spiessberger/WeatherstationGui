#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlError>

#include "homescreendata.h"
#include "iconprovider.h"
#include "indoorclimatedata.h"
#include "weatherstationdata.h"

int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("weatherdata.sqlite");
  if (!database.open())
  {
    qWarning() << "failed to open database:" << database.lastError();
    return 1;
  }

  wsgui::data::IndoorClimateData indoorClimateData{database};
  wsgui::data::WeatherStationData weatherStationData{database};
  wsgui::data::HomeScreenData homeScreenData(indoorClimateData, weatherStationData);
  wsgui::data::HomeScreenData::setQmlInstance(&homeScreenData);


  QQmlApplicationEngine engine;
  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreationFailed,
      &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.addImageProvider(wsgui::IconProviderHelper::ImageProviderId, new wsgui::IconProvider());
  engine.loadFromModule("WeatherstationGui", "Main");

  return app.exec();
}
