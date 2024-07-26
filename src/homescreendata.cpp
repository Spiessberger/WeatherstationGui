#include "homescreendata.h"

#include <chrono>

using namespace std::chrono_literals;

namespace wsgui
{
namespace data
{

HomeScreenData* HomeScreenData::qmlInstance = nullptr;

HomeScreenData::HomeScreenData(const IndoorClimateData& indoorClimateData,
                               const WeatherStationData& weatherStationData,
                               QObject* parent)
    : QObject(parent)
    , m_indoorClimateData(indoorClimateData)
    , m_weatherStationData(weatherStationData)
{
  connect(&m_dateTimeUpdateTimer, &QTimer::timeout, this, &HomeScreenData::updateDateTime);
  updateDateTime();
  m_dateTimeUpdateTimer.start(1s);

  connect(&m_indoorClimateData,
          &IndoorClimateData::recentIndoorDataChanged,
          this,
          &HomeScreenData::updateIndoorClimateData);
  connect(&m_weatherStationData,
          &WeatherStationData::recentWeatherDataChanged,
          this,
          &HomeScreenData::updateWeatherStationData);
}

void HomeScreenData::setQmlInstance(HomeScreenData* qmlInstance)
{
  Q_ASSERT(qmlInstance != nullptr);
  Q_ASSERT(HomeScreenData::qmlInstance == nullptr);
  HomeScreenData::qmlInstance = qmlInstance;
}

HomeScreenData* HomeScreenData::create(QQmlEngine*, QJSEngine*)
{
  Q_ASSERT(qmlInstance != nullptr);
  QQmlEngine::setObjectOwnership(qmlInstance, QQmlEngine::CppOwnership);
  return qmlInstance;
}

QString HomeScreenData::date() const
{
  return m_date.toString();
}

void HomeScreenData::setDate(const QDate& newDate)
{
  if (m_date == newDate)
    return;
  m_date = newDate;
  emit dateChanged();
}

QString HomeScreenData::time() const
{
  return m_time.toString();
}

void HomeScreenData::setTime(const QTime& newTime)
{
  if (m_time == newTime)
    return;
  m_time = newTime;
  emit timeChanged();
}

IndoorClimateDataDisplay* HomeScreenData::indoorClimateDataDisplay()
{
  return &m_indoorClimateDataDisplay;
}

WeatherStationDataDisplay* HomeScreenData::weatherStationDataDisplay()
{
  return &m_weatherStationDataDisplay;
}

void HomeScreenData::updateDateTime()
{
  const QDateTime currentDateTime = QDateTime::currentDateTime();
  setTime(currentDateTime.time());
  setDate(currentDateTime.date());
}

void HomeScreenData::updateWeatherStationData()
{
  m_weatherStationDataDisplay.update(m_weatherStationData.recentWeatherData());
}

void HomeScreenData::updateIndoorClimateData()
{
  m_indoorClimateDataDisplay.update(m_indoorClimateData.recentIndoorData());
}

} // namespace data
} // namespace wsgui
