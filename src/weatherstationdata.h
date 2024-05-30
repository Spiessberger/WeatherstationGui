#pragma once

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>

#include "measurement.h"

namespace wsgui
{
namespace data
{

struct WeatherStationDataSet
{
  QDateTime timeStamp;
  Measurement<float, Unit::DegreeCelsius> temperature;
  Measurement<float, Unit::Percent> humidity;
  Measurement<float, Unit::KilometersPerHour> windSpeed;
  Measurement<float, Unit::KilometersPerHour> windGust;
  Measurement<int, Unit::Degree> windDirection;
  Measurement<float, Unit::MilliMeter> rain;
};

class WeatherStationData : public QObject
{
  Q_OBJECT
public:
  explicit WeatherStationData(QSqlDatabase& database);

  void addWeatherData(const WeatherStationDataSet& weatherData);

  const WeatherStationDataSet& recentWeatherData() const;
  std::vector<WeatherStationDataSet> getWeatherData(const QDateTime& from, const QDateTime& to);

signals:
  void recentWeatherDataChanged();

private:
  void prepareDatabase();
  void insertWeatherData(const WeatherStationDataSet& weatherData);

  WeatherStationDataSet m_recentWeatherData;
  QSqlDatabase& m_database;
};

} // namespace data
} // namespace wsgui
