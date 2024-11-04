#pragma once

#include <QDateTime>

namespace wsgui
{
namespace data
{

struct WeatherData
{
  int id = 0;
  QDateTime timestamp;
  float temperature = 0.0;
  float humidity = 0.0;
  float windSpeed = 0.0;
  float windGust = 0.0;
  int windDirection = 0;
  float rain = 0.0;
};

} // namespace data
} // namespace wsgui
