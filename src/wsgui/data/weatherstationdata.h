#pragma once

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>

#include <wsgui_global.h>

#include "weatherstationdataset.h"

namespace wsgui
{
namespace data
{

class WSGUI_EXPORT WeatherStationData : public QObject
{
  Q_OBJECT
public:
  explicit WeatherStationData(QSqlDatabase& database);

  void addWeatherData(const WeatherStationDataSet& dataSet);

  const WeatherStationDataSet& recentWeatherData() const;
  std::vector<WeatherStationDataSet> getWeatherData(const QDateTime& from, const QDateTime& to);

signals:
  void recentWeatherDataChanged();

private:
  void prepareDatabase();
  void insertWeatherData(const WeatherStationDataSet& dataSet);

  WeatherStationDataSet m_recentWeatherData;
  QSqlDatabase& m_database;
};

} // namespace data
} // namespace wsgui
