#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include <wsgui_global.h>

#include "indoorclimatedata.h"
#include "indoorclimatedatadisplay.h"
#include "weatherstationdata.h"
#include "weatherstationdatadisplay.h"

namespace wsgui
{
namespace data
{

class WSGUI_EXPORT HomeScreenData : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QString date READ date NOTIFY dateChanged FINAL)
  Q_PROPERTY(QString time READ time NOTIFY timeChanged FINAL)
  Q_PROPERTY(IndoorClimateDataDisplay* indoorClimate READ indoorClimateDataDisplay CONSTANT FINAL)
  Q_PROPERTY(
      WeatherStationDataDisplay* weatherStation READ weatherStationDataDisplay CONSTANT FINAL)

public:
  explicit HomeScreenData(const IndoorClimateData& indoorClimateData,
                          const WeatherStationData& weatherStationData);

  static void setQmlInstance(HomeScreenData* qmlInstance);
  static HomeScreenData* create(QQmlEngine*, QJSEngine*);

  QString date() const;
  QString time() const;

  IndoorClimateDataDisplay* indoorClimateDataDisplay();
  WeatherStationDataDisplay* weatherStationDataDisplay();

signals:
  void dateChanged();
  void timeChanged();

private:
  static HomeScreenData* qmlInstance;

  void setDate(const QDate& newDate);
  void setTime(const QTime& newTime);
  void updateDateTime();
  void updateWeatherStationData();
  void updateIndoorClimateData();

  QDate m_date;
  QTime m_time;
  QTimer m_dateTimeUpdateTimer;
  const IndoorClimateData& m_indoorClimateData;
  const WeatherStationData& m_weatherStationData;
  IndoorClimateDataDisplay m_indoorClimateDataDisplay;
  WeatherStationDataDisplay m_weatherStationDataDisplay;
};

} // namespace data
} // namespace wsgui
