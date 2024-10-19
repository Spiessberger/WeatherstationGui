#pragma once

#include <QObject>
#include <QQmlEngine>

#include <wsgui_global.h>

#include "measurement.h"

namespace wsgui
{
namespace data
{

class WSGUI_EXPORT DisplayData : public QObject
{
  Q_OBJECT
  QML_ANONYMOUS

  Q_PROPERTY(QString value READ value NOTIFY valueChanged FINAL)
  Q_PROPERTY(QString unit READ unit NOTIFY unitChanged FINAL)

public:
  explicit DisplayData(QObject* parent = nullptr);

  template<Unit unit>
  void setMeasurement(const Measurement<float, unit>& measurement);

  const QString& value() const;
  void setValue(const QString& newValue);

  QString unit() const;
  void setUnit(Unit newUnit);

signals:
  void valueChanged();
  void unitChanged();

private:
  QString m_value;
  Unit m_unit = Unit::None;
};

template<Unit u>
void DisplayData::setMeasurement(const Measurement<float, u>& measurement)
{
  setValue(QString::number(measurement.value, 'f', 1));
  setUnit(u);
}

} // namespace data
} // namespace wsgui
