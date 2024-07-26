#include "indoorclimatedata.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

namespace wsgui
{
namespace data
{

namespace
{
namespace dbfields
{
const char* table = "indoorclimate";
const char* timestamp = "timestamp";
const char* temperature = "temperature";
const char* humidity = "humidity";
} // namespace dbfields
} // namespace

IndoorClimateData::IndoorClimateData(QSqlDatabase& database)
    : m_database(database)
{
  prepareDatabase();
}

void IndoorClimateData::addIndoorData(const IndoorClimateDataSet& dataSet)
{
  insertIndoorData(dataSet);

  if (dataSet.timeStamp >= m_recentIndoorData.timeStamp)
  {
    m_recentIndoorData = dataSet;
    emit recentIndoorDataChanged();
  }
}

const IndoorClimateDataSet& IndoorClimateData::recentIndoorData() const
{
  return m_recentIndoorData;
}

std::vector<IndoorClimateDataSet> IndoorClimateData::getIndoorData(const QDateTime& from,
                                                                   const QDateTime& to)
{
  static const QString selectQuery = QStringLiteral("SELECT * FROM %1 WHERE %2 >= ? AND %2 <= ?")
                                         .arg(dbfields::table)
                                         .arg(dbfields::timestamp);

  std::vector<IndoorClimateDataSet> ret;

  QSqlQuery q{m_database};
  q.prepare(selectQuery);

  q.addBindValue(from);
  q.addBindValue(to);

  if (!q.exec())
  {
    qWarning() << "failed to get weatherdata from" << from << "to" << to << ":" << q.lastError();
    return ret;
  }

  const int timestampIndex = q.record().indexOf(dbfields::timestamp);
  const int temperatureIndex = q.record().indexOf(dbfields::temperature);
  const int humidityIndex = q.record().indexOf(dbfields::humidity);

  while (q.next())
  {
    IndoorClimateDataSet dataSet;

    dataSet.timeStamp = q.value(timestampIndex).toDateTime();
    dataSet.temperature = q.value(temperatureIndex).toFloat();
    dataSet.humidity = q.value(humidityIndex).toFloat();

    ret.emplace_back(std::move(dataSet));
  }

  return ret;
}

void IndoorClimateData::prepareDatabase()
{
  static const QString createTableQuery = QStringLiteral("CREATE TABLE %1("
                                                         "id INTEGER PRIMARY KEY,"
                                                         "%2 DATETIME,"
                                                         "%3 REAL,"
                                                         "%4 REAL)")
                                              .arg(dbfields::table)       // 1
                                              .arg(dbfields::timestamp)   // 2
                                              .arg(dbfields::temperature) // 3
                                              .arg(dbfields::humidity);   // 4

  if (m_database.tables().contains(dbfields::table))
  {
    return;
  }

  QSqlQuery q{m_database};

  if (q.exec(createTableQuery))
  {
    qDebug() << "created table" << dbfields::table;
  }
  else
  {
    qWarning() << "failed to create" << dbfields::table << "table:" << q.lastError();
  }
}

void IndoorClimateData::insertIndoorData(const IndoorClimateDataSet& indoorData)
{
  static const QString insertQuery = QStringLiteral("INSERT INTO %1 (%2, %3, %4) "
                                                    "VALUES (?, ?, ?)")
                                         .arg(dbfields::table)       // 1
                                         .arg(dbfields::timestamp)   // 2
                                         .arg(dbfields::temperature) // 3
                                         .arg(dbfields::humidity);   // 4

  QSqlQuery q{m_database};

  if (q.prepare(insertQuery))
  {
    q.addBindValue(indoorData.timeStamp);
    q.addBindValue(indoorData.temperature.value);
    q.addBindValue(indoorData.humidity.value);
    if (!q.exec())
    {
      qWarning() << "failed to execute insert:" << q.lastError();
    }
  }
  else
  {
    qWarning() << "failed to prepare insert query:" << q.lastError();
  }
}

} // namespace data
} // namespace wsgui
