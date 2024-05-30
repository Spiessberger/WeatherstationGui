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
  explicit Measurement(const T& value_)
      : value(value_)
  {
  }

  T value = {};

  Measurement& operator=(const T& value)
  {
    this->value = value;
    return *this;
  }

  static const Unit unit = unit_;
};

} // namespace data
} // namespace wsgui
