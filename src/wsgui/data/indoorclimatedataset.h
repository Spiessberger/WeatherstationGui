#pragma once

#include <QDateTime>

#include "measurement.h"

namespace wsgui
{
namespace data
{

struct IndoorClimateDataSet
{
  QDateTime timeStamp;
  Measurement<float, Unit::DegreeCelsius> temperature;
  Measurement<float, Unit::Percent> humidity;
};

} // namespace data
} // namespace wsgui
