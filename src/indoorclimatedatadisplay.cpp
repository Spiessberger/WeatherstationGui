#include "indoorclimatedatadisplay.h"

namespace wsgui
{
namespace data
{

IndoorClimateDataDisplay::IndoorClimateDataDisplay(QObject* parent)
    : QObject(parent)
{
}

DisplayData* IndoorClimateDataDisplay::temperature()
{
  return &m_temperature;
}

DisplayData* IndoorClimateDataDisplay::humidity()
{
  return &m_humidity;
}

void IndoorClimateDataDisplay::update(const IndoorClimateDataSet& dataset)
{
  m_temperature.setMeasurement(dataset.temperature);
  m_humidity.setMeasurement(dataset.humidity);
}

} // namespace data
} // namespace wsgui
