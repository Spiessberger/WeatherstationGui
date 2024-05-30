#pragma once

#include <QObject>
#include <QQmlEngine>

#include "weatherstationdata.h"

namespace wsgui
{
namespace data
{

class HomeScreenData : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
public:
  explicit HomeScreenData(const WeatherStationData& weatherStationData, QObject* parent = nullptr);

  static void setQmlInstance(HomeScreenData* qmlInstance);

signals:

private:
  static HomeScreenData* qmlInstance;
  const WeatherStationData& m_weatherStationData;
};

} // namespace data
} // namespace wsgui
