#include "sqliteroomclimatedao.h"

#include <QLoggingCategory>
#include <QSqlError>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui.data.SQLiteRoomClimateDAO")
}

namespace wsgui
{
namespace data
{

SQLiteRoomClimateDAO::SQLiteRoomClimateDAO(SQLiteDatabase& database)
    : m_database(database)
{
}

bool SQLiteRoomClimateDAO::initialize()
{
  const QString createTableQuery = R"(
    CREATE TABLE IF NOT EXISTS room_climate (
      id          INTEGER PRIMARY KEY,
      timestamp   DATETIME NOT NULL,
      temperature REAL NOT NULL,
      humidity    REAL NOT NULL
    );
  )";

  const QString createIndexQuery = R"(
    CREATE INDEX IF NOT EXISTS idx_room_climate_timestamp ON room_climate (timestamp);
  )";

  QSqlQuery q = m_database.query();
  if (!q.exec(createTableQuery))
  {
    qCWarning(log) << "failed to create room climate table:" << q.lastError().text();
    return false;
  }

  q = m_database.query();
  if (!q.exec(createIndexQuery))
  {
    qCWarning(log) << "failed to create index for room climate table:" << q.lastError().text();
    return false;
  }

  return true;
}

bool SQLiteRoomClimateDAO::insert(const RoomClimateData& roomClimateData)
{
  Q_UNUSED(roomClimateData);
  return false;
}

std::vector<RoomClimateData> SQLiteRoomClimateDAO::getData(const QDateTime& from,
                                                           const QDateTime& to)
{
  Q_UNUSED(from)
  Q_UNUSED(to)

  return {};
}

int SQLiteRoomClimateDAO::numEntries(const QDateTime& from, const QDateTime& to)
{
  Q_UNUSED(from)
  Q_UNUSED(to)

  return 0;
}

} // namespace data
} // namespace wsgui
