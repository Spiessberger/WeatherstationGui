#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "weatherstationdata.h"

namespace wsgui
{
namespace data
{

class HomeScreenData : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QString date READ date NOTIFY dateChanged FINAL)
  Q_PROPERTY(QString time READ time NOTIFY timeChanged FINAL)
public:
  explicit HomeScreenData(const WeatherStationData& weatherStationData, QObject* parent = nullptr);

  static void setQmlInstance(HomeScreenData* qmlInstance);

  QString date() const;
  QString time() const;

signals:
  void dateChanged();
  void timeChanged();

private:
  static HomeScreenData* qmlInstance;

  void setDate(const QDate& newDate);
  void setTime(const QTime& newTime);
  void updateDateTime();

  QDate m_date;
  QTime m_time;
  QTimer m_dateTimeUpdateTimer;
  const WeatherStationData& m_weatherStationData;
};

} // namespace data
} // namespace wsgui
