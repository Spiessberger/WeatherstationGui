#pragma once

#include <QDateTime>

#include "measurement.h"

namespace wsgui
{
namespace data
{

struct WeatherStationDataSet
{
  QDateTime timeStamp;
  Measurement<float, Unit::DegreeCelsius> temperature;
  Measurement<float, Unit::Percent> humidity;
  Measurement<float, Unit::KilometersPerHour> windSpeed;
  Measurement<float, Unit::KilometersPerHour> windGust;
  Measurement<int, Unit::Degree> windDirection;
  Measurement<float, Unit::MilliMeter> rain;
};

} // namespace data
} // namespace wsgui
