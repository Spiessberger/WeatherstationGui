#include "weatherstationdatadisplay.h"

namespace wsgui
{
namespace data
{

WeatherStationDataDisplay::WeatherStationDataDisplay(QObject* parent)
    : QObject{parent}
{
}

DisplayData* WeatherStationDataDisplay::temperature()
{
  return &m_temperature;
}

DisplayData* WeatherStationDataDisplay::humidity()
{
  return &m_humidity;
}

DisplayData* WeatherStationDataDisplay::windSpeed()
{
  return &m_windSpeed;
}

DisplayData* WeatherStationDataDisplay::windGust()
{
  return &m_windGust;
}

DisplayData* WeatherStationDataDisplay::rain()
{
  return &m_rain;
}

int WeatherStationDataDisplay::windDirection() const
{
  return m_windDirection;
}

void WeatherStationDataDisplay::update(const WeatherStationDataSet& dataset)
{
  m_temperature.setMeasurement(dataset.temperature);
  m_humidity.setMeasurement(dataset.humidity);
  m_windSpeed.setMeasurement(dataset.windSpeed);
  m_windGust.setMeasurement(dataset.windGust);
  if (dataset.windDirection.value != m_windDirection)
  {
    m_windDirection = dataset.windDirection.value;
    emit windDirectionChanged();
  }
}

} // namespace data
} // namespace wsgui
