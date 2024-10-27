#include "displaydata.h"

namespace wsgui
{
namespace data
{

const QString& DisplayData::value() const
{
  return m_value;
}

QString DisplayData::unit() const
{
  switch (m_unit)
  {
    case Unit::KilometersPerHour:
      return QStringLiteral("km/h");
    case Unit::Percent:
      return QStringLiteral("%");
    case Unit::DegreeCelsius:
      return QStringLiteral("ºC");
    case Unit::Degree:
      return QStringLiteral("º");
    case Unit::MilliMeter:
      return QStringLiteral("mm");
    case Unit::None:
    default:
      return QStringLiteral("");
  }
}

void DisplayData::setValue(const QString& newValue)
{
  if (m_value == newValue)
    return;

  m_value = newValue;
  emit valueChanged();
}

void DisplayData::setUnit(Unit newUnit)
{
  if (m_unit == newUnit)
    return;

  m_unit = newUnit;
  emit unitChanged();
}

} // namespace data
} // namespace wsgui
