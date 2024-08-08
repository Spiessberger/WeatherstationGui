#include "weatherstationdata.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

namespace wsgui
{
namespace data
{

namespace
{
namespace dbfields
{
const char* table = "weatherstation";
const char* timestamp = "timestamp";
const char* temperature = "temperature";
const char* humidity = "humidity";
const char* windSpeed = "wind_speed";
const char* windGust = "wind_gust";
const char* windDirection = "wind_direction";
const char* rain = "rain";
} // namespace dbfields
} // namespace

WeatherStationData::WeatherStationData(QSqlDatabase& database)
    : m_database(database)
{
  prepareDatabase();
}

void WeatherStationData::addWeatherData(const WeatherStationDataSet& dataSet)
{
  insertWeatherData(dataSet);

  if (dataSet.timeStamp >= m_recentWeatherData.timeStamp)
  {
    m_recentWeatherData = dataSet;
    emit recentWeatherDataChanged();
  }
}

std::vector<WeatherStationDataSet> WeatherStationData::getWeatherData(const QDateTime& from,
                                                                      const QDateTime& to)
{
  static const QString selectQuery =
      QStringLiteral("SELECT * FROM %1 WHERE %2 >= :from AND %2 <= :to")
          .arg(dbfields::table)
          .arg(dbfields::timestamp);

  std::vector<WeatherStationDataSet> ret;

  QSqlQuery q{m_database};
  q.prepare(selectQuery);

  q.bindValue(":from", from);
  q.bindValue(":to", to);

  if (!q.exec())
  {
    qWarning() << "failed to get weatherdata from" << from << "to" << to << ":" << q.lastError();
    return ret;
  }

  const QSqlRecord record = q.record();
  const int timestampIndex = record.indexOf(dbfields::timestamp);
  const int temperatureIndex = record.indexOf(dbfields::temperature);
  const int humidityIndex = record.indexOf(dbfields::humidity);
  const int windSpeedIndex = record.indexOf(dbfields::windSpeed);
  const int windGustIndex = record.indexOf(dbfields::windGust);
  const int windDirectionIndex = record.indexOf(dbfields::windDirection);
  const int rainIndex = record.indexOf(dbfields::rain);

  while (q.next())
  {
    WeatherStationDataSet dataSet;

    dataSet.timeStamp = q.value(timestampIndex).toDateTime();
    dataSet.temperature = q.value(temperatureIndex).toFloat();
    dataSet.humidity = q.value(humidityIndex).toFloat();
    dataSet.windSpeed = q.value(windSpeedIndex).toFloat();
    dataSet.windGust = q.value(windGustIndex).toFloat();
    dataSet.windDirection = q.value(windDirectionIndex).toFloat();
    dataSet.rain = q.value(rainIndex).toFloat();

    ret.emplace_back(std::move(dataSet));
  }

  return ret;
}

void WeatherStationData::prepareDatabase()
{
  static const QString createTableQuery = QStringLiteral("CREATE TABLE %1("
                                                         "id INTEGER PRIMARY KEY,"
                                                         "%2 DATETIME,"
                                                         "%3 REAL,"
                                                         "%4 REAL,"
                                                         "%5 REAL,"
                                                         "%6 REAL,"
                                                         "%7 INTEGER,"
                                                         "%8 REAL)")
                                              .arg(dbfields::table)         // 1
                                              .arg(dbfields::timestamp)     // 2
                                              .arg(dbfields::temperature)   // 3
                                              .arg(dbfields::humidity)      // 4
                                              .arg(dbfields::windSpeed)     // 5
                                              .arg(dbfields::windGust)      // 6
                                              .arg(dbfields::windDirection) // 7
                                              .arg(dbfields::rain);         // 8

  if (m_database.tables().contains(dbfields::table))
  {
    return;
  }

  QSqlQuery q{m_database};

  if (q.exec(createTableQuery))
  {
    qDebug() << "created table" << dbfields::table;
  }
  else
  {
    qWarning() << "failed to create" << dbfields::table << "table:" << q.lastError();
  }
}

void WeatherStationData::insertWeatherData(const WeatherStationDataSet& weatherData)
{
  static const QString insertQuery = QStringLiteral("INSERT INTO %1 (%2, %3, %4, %5, %6, %7, %8) "
                                                    "VALUES (:%2, :%3, :%4, :%5, :%6, :%7, :%8)")
                                         .arg(dbfields::table)         // 1
                                         .arg(dbfields::timestamp)     // 2
                                         .arg(dbfields::temperature)   // 3
                                         .arg(dbfields::humidity)      // 4
                                         .arg(dbfields::windSpeed)     // 5
                                         .arg(dbfields::windGust)      // 6
                                         .arg(dbfields::windDirection) // 7
                                         .arg(dbfields::rain);         // 8

  QSqlQuery q{m_database};

  if (!q.prepare(insertQuery))
  {
    qWarning() << "failed to prepare insert query:" << q.lastError();
    return;
  }

  q.bindValue(QString{":"} + dbfields::timestamp, weatherData.timeStamp);
  q.bindValue(QString{":"} + dbfields::temperature, weatherData.temperature.value);
  q.bindValue(QString{":"} + dbfields::humidity, weatherData.humidity.value);
  q.bindValue(QString{":"} + dbfields::windSpeed, weatherData.windSpeed.value);
  q.bindValue(QString{":"} + dbfields::windGust, weatherData.windGust.value);
  q.bindValue(QString{":"} + dbfields::windDirection, weatherData.windDirection.value);
  q.bindValue(QString{":"} + dbfields::rain, weatherData.rain.value);

  if (!q.exec())
  {
    qWarning() << "failed to execute insert:" << q.lastError();
  }
}

const WeatherStationDataSet& WeatherStationData::recentWeatherData() const
{
  return m_recentWeatherData;
}

} // namespace data
} // namespace wsgui
