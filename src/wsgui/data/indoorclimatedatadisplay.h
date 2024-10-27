#pragma once

#include <QObject>
#include <QQmlEngine>

#include <wsgui_global.h>

#include "displaydata.h"
#include "indoorclimatedataset.h"

namespace wsgui
{
namespace data
{

class WSGUI_EXPORT IndoorClimateDataDisplay : public QObject
{
  Q_OBJECT
  QML_ANONYMOUS

  Q_PROPERTY(DisplayData* temperature READ temperature CONSTANT FINAL)
  Q_PROPERTY(DisplayData* humidity READ humidity CONSTANT FINAL)
public:
  IndoorClimateDataDisplay() = default;

  DisplayData* temperature();
  DisplayData* humidity();

  void update(const IndoorClimateDataSet& dataset);

private:
  DisplayData m_temperature;
  DisplayData m_humidity;
};

} // namespace data
} // namespace wsgui
