#pragma once

namespace wsgui
{
namespace data
{

enum class Unit
{
  None,
  KilometersPerHour,
  Percent,
  DegreeCelsius,
  Degree,
  MilliMeter
};

template<typename T, Unit u>
struct Measurement
{
  Measurement() = default;
  explicit Measurement(const T& v)
      : value(v)
  {
  }

  T value = {};

  Measurement& operator=(const T& value)
  {
    this->value = value;
    return *this;
  }

  static const Unit unit = u;
};

} // namespace data
} // namespace wsgui
