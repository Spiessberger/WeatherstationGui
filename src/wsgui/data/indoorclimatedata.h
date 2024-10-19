#pragma once

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>

#include <wsgui_global.h>

#include "indoorclimatedataset.h"

namespace wsgui
{
namespace data
{

class WSGUI_EXPORT IndoorClimateData : public QObject
{
  Q_OBJECT
public:
  explicit IndoorClimateData(QSqlDatabase& database);

  void addIndoorData(const IndoorClimateDataSet& indoorData);

  const IndoorClimateDataSet& recentIndoorData() const;
  std::vector<IndoorClimateDataSet> getIndoorData(const QDateTime& from, const QDateTime& to);

signals:
  void recentIndoorDataChanged();

private:
  void prepareDatabase();
  void insertIndoorData(const IndoorClimateDataSet& indoorData);

  IndoorClimateDataSet m_recentIndoorData;
  QSqlDatabase& m_database;
};

} // namespace data
} // namespace wsgui
