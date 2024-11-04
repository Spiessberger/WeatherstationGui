#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <core/iconprovider.h>

#include <data/sqlitedatabase.h>
#include <data/sqliteroomclimatedao.h>
#include <data/sqliteweatherdatadao.h>
#include <data/weatherdatamodel.h>

int main(int argc, char* argv[])
{
  Q_INIT_RESOURCE(resources);
  QGuiApplication app(argc, argv);

  wsgui::data::SQLiteDatabase database;
  if (!database.initialize("weather_data.sqlite"))
  {
    return 1;
  }

  wsgui::data::SQLiteRoomClimateDAO roomClimateDAO{database};
  if (!roomClimateDAO.initialize())
  {
    return 1;
  }
  wsgui::data::SQLiteWeatherDataDAO weatherDataDAO{database};
  if (!weatherDataDAO.initialize())
  {
    return 1;
  }

  wsgui::data::WeatherDataModel::setDataAccessObject(&weatherDataDAO);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreationFailed,
      &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.addImageProvider(wsgui::core::IconProviderHelper::ImageProviderId,
                          new wsgui::core::IconProvider());
  engine.loadFromModule("WeatherstationGui", "Main");

  return app.exec();
}
