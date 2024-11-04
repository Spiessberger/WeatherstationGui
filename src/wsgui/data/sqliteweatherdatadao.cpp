#include "sqliteweatherdatadao.h"

#include <QLoggingCategory>
#include <QSqlError>
#include <QSqlRecord>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui.data.SQLiteWeatherDataDAO")
}

namespace wsgui
{
namespace data
{

SQLiteWeatherDataDAO::SQLiteWeatherDataDAO(SQLiteDatabase& database)
    : m_database(database)
{
}

bool SQLiteWeatherDataDAO::initialize()
{
  const QString createTableQuery = R"(
    CREATE TABLE IF NOT EXISTS weather_data (
      id              INTEGER PRIMARY KEY,
      timestamp       DATETIME NOT NULL,
      temperature     REAL NOT NULL,
      humidity        REAL NOT NULL,
      wind_speed      REAL NOT NULL,
      wind_gust       REAL NOT NULL,
      wind_direction  INTEGER NOT NULL,
      rain            REAL NOT NULL
    );
  )";

  const QString createIndexQuery = R"(
    CREATE INDEX IF NOT EXISTS idx_weather_data_timestamp ON weather_data (timestamp);
  )";

  QSqlQuery q = m_database.query();
  if (!q.exec(createTableQuery))
  {
    qCWarning(log) << "failed to create weather data table:" << q.lastError().text();
    return false;
  }

  q = m_database.query();
  if (!q.exec(createIndexQuery))
  {
    qCWarning(log) << "failed to create index for weather data table:" << q.lastError().text();
    return false;
  }

  return true;
}

bool SQLiteWeatherDataDAO::insert(const WeatherData& weatherData)
{
  const QString insertQuery = R"(
    INSERT INTO weather_data (
      timestamp,
      temperature,
      humidity,
      wind_speed,
      wind_gust,
      wind_direction,
      rain
    )
    VALUES (
      :timestamp,
      :temperature,
      :humidity,
      :wind_speed,
      :wind_gust,
      :wind_direction,
      :rain
    );
  )";

  QSqlQuery q = m_database.query();

  if (!q.prepare(insertQuery))
  {
    qCWarning(log) << "failed to prepare insert query:" << q.lastError().text();
    return false;
  }

  q.bindValue(":timestamp", weatherData.timestamp);
  q.bindValue(":temperature", weatherData.temperature);
  q.bindValue(":humidity", weatherData.humidity);
  q.bindValue(":wind_speed", weatherData.windSpeed);
  q.bindValue(":wind_gust", weatherData.windGust);
  q.bindValue(":wind_direction", weatherData.windDirection);
  q.bindValue(":rain", weatherData.rain);

  if (!q.exec())
  {
    qCWarning(log) << "failed to insert weather data:" << q.lastError().text();
    return false;
  }

  return true;
}

std::vector<WeatherData> SQLiteWeatherDataDAO::getData(const QDateTime& from, const QDateTime& to)
{
  const QString selectQuery = R"(
    SELECT
      id,
      timestamp,
      temperature,
      humidity,
      wind_speed,
      wind_gust,
      wind_direction,
      rain
    FROM weather_data
    WHERE timestamp BETWEEN :from AND :to
    ORDER BY timestamp;
  )";

  QSqlQuery q = m_database.query();

  if (!q.prepare(selectQuery))
  {
    qCWarning(log) << "failed to prepare select query:" << q.lastError().text();
    return {};
  }

  q.bindValue(":from", from);
  q.bindValue(":to", to);

  if (!q.exec())
  {
    qCWarning(log) << "failed to get weather data:" << q.lastError().text();
    return {};
  }

  const QSqlRecord record = q.record();

  const int idIndex = record.indexOf("id");
  const int timestampIndex = record.indexOf("timestamp");
  const int temperatureIndex = record.indexOf("temperature");
  const int humidityIndex = record.indexOf("humidity");
  const int windSpeedIndex = record.indexOf("wind_speed");
  const int windGustIndex = record.indexOf("wind_gust");
  const int windDirectionIndex = record.indexOf("wind_direction");
  const int rainIndex = record.indexOf("rain");

  std::vector<WeatherData> ret;
  WeatherData data;
  while (q.next())
  {
    data.id = q.value(idIndex).toInt();
    data.timestamp = q.value(timestampIndex).toDateTime();
    data.temperature = q.value(temperatureIndex).toFloat();
    data.humidity = q.value(humidityIndex).toFloat();
    data.windSpeed = q.value(windSpeedIndex).toFloat();
    data.windGust = q.value(windGustIndex).toFloat();
    data.windDirection = q.value(windDirectionIndex).toInt();
    data.rain = q.value(rainIndex).toFloat();

    ret.push_back(data);
  }

  return ret;
}

int SQLiteWeatherDataDAO::numEntries(const QDateTime& from, const QDateTime& to)
{
  const QString selectQuery = R"(
    SELECT COUNT(*) AS count
    FROM weather_data
    WHERE timestamp BETWEEN :from AND :to
  )";

  QSqlQuery q = m_database.query();

  if (!q.prepare(selectQuery))
  {
    qCWarning(log) << "failed to prepare select query:" << q.lastError().text();
    return 0;
  }

  q.bindValue(":from", from);
  q.bindValue(":to", to);

  if (!q.exec())
  {
    qCWarning(log) << "failed to number of weather data entries:" << q.lastError().text();
    return 0;
  }

  return q.value("count").toInt();
}

} // namespace data
} // namespace wsgui
