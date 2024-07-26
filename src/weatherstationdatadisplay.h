#pragma once

#include <QObject>
#include <QQmlEngine>

#include "displaydata.h"
#include "weatherstationdataset.h"

namespace wsgui
{
namespace data
{

class WeatherStationDataDisplay : public QObject
{
  Q_OBJECT
  QML_ANONYMOUS

  Q_PROPERTY(DisplayData* temperature READ temperature CONSTANT FINAL)
  Q_PROPERTY(DisplayData* humidity READ humidity CONSTANT FINAL)
  Q_PROPERTY(DisplayData* windSpeed READ windSpeed CONSTANT FINAL)
  Q_PROPERTY(DisplayData* windGust READ windGust CONSTANT FINAL)
  Q_PROPERTY(DisplayData* rain READ rain CONSTANT FINAL)
  Q_PROPERTY(int windDirection READ windDirection NOTIFY windDirectionChanged FINAL)
public:
  explicit WeatherStationDataDisplay(QObject* parent = nullptr);

  DisplayData* temperature();
  DisplayData* humidity();
  DisplayData* windSpeed();
  DisplayData* windGust();
  DisplayData* rain();
  int windDirection() const;

  void update(const WeatherStationDataSet& dataset);

signals:
  void windDirectionChanged();

private:
  DisplayData m_temperature;
  DisplayData m_humidity;
  DisplayData m_windSpeed;
  DisplayData m_windGust;
  DisplayData m_rain;
  int m_windDirection = 0;
};

} // namespace data
} // namespace wsgui
