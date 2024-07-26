#include "homescreendata.h"

namespace wsgui
{
namespace data
{
HomeScreenData* HomeScreenData::qmlInstance = nullptr;

HomeScreenData::HomeScreenData(const WeatherStationData& weatherStationData, QObject* parent)
    : QObject(parent)
    , m_weatherStationData(weatherStationData)
{
  connect(&m_dateTimeUpdateTimer, &QTimer::timeout, this, &HomeScreenData::updateDateTime);
  updateDateTime();
  m_dateTimeUpdateTimer.start(1s);
}

void HomeScreenData::setQmlInstance(HomeScreenData* qmlInstance)
{
  Q_ASSERT(qmlInstance != nullptr);
  Q_ASSERT(HomeScreenData::qmlInstance == nullptr);
  HomeScreenData::qmlInstance = qmlInstance;
}
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

void HomeScreenData::updateDateTime()
{
  const QDateTime currentDateTime = QDateTime::currentDateTime();
  setTime(currentDateTime.time());
  setDate(currentDateTime.date());
}

} // namespace data
} // namespace wsgui
