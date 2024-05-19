#include "weatherstationdata.h"

namespace wsgui
{
namespace data
{

WeatherStationData::WeatherStationData(QObject* parent)
    : QObject{parent}
{
  m_database = QSqlDatabase::addDatabase("QSQLITE");
  m_database.setDatabaseName("weatherdata.sqlite");
  if (!m_database.open())
  {
    qWarning() << "failed to open database";
  }
}

void WeatherStationData::addWeatherData(const WeatherStationDataSet& dataSet)
{
  // store dataset to database

  if (dataSet.timeStamp >= m_recentWeatherData.timeStamp)
  {
    m_recentWeatherData = dataSet;
    emit recentWeatherDataChanged();
  }
}

std::vector<WeatherStationDataSet> WeatherStationData::getWeatherData(const QDateTime& from,
                                                                      const QDateTime& to)
{
  std::vector<WeatherStationDataSet> ret;

  return ret;
}

const WeatherStationDataSet& WeatherStationData::recentWeatherData() const
{
  return m_recentWeatherData;
}

} // namespace data
} // namespace wsgui
