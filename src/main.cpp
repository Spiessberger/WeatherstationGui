#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlError>

#include "weatherstationdata.h"

int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName(
      "C:\\Users\\Daniel_\\Projects\\weatherstation\\CsvToSQLite\\build\\Desktop_Qt_6_7_0_MinGW_64_"
      "bit-Debug\\weaterdata.sqlite");
  if (!database.open())
  {
    qWarning() << "failed to open database:" << database.lastError();
    return 1;
  }

  wsgui::data::WeatherStationData weatherStationData{database};

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreationFailed,
      &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.loadFromModule("WeatherstationGui", "Main");

  return app.exec();
}
