#pragma once

#include <QDateTime>

namespace wsgui
{
namespace data
{

struct RoomClimateData
{
  int id = 0;
  QDateTime timestamp;
  float temperature = 0.0;
  float humidity = 0.0;
};

} // namespace data
} // namespace wsgui
