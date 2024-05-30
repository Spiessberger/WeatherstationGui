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
}

void HomeScreenData::setQmlInstance(HomeScreenData* qmlInstance)
{
  Q_ASSERT(qmlInstance != nullptr);
  Q_ASSERT(HomeScreenData::qmlInstance == nullptr);
  HomeScreenData::qmlInstance = qmlInstance;
}

} // namespace data
} // namespace wsgui
