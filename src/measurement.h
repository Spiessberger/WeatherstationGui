#pragma once

namespace wsgui
{
namespace data
{

enum class Unit
{
  KilometersPerHour,
  Percent,
  DegreeCelsius,
  Degree,
  MilliMeter
};

template<typename T, Unit unit_>
struct Measurement
{
  Measurement() = default;
  Measurement(const T& value_)
      : value(value_)
  {
  }

  T value = {};
  static const Unit unit = unit_;
};

} // namespace data
} // namespace wsgui
