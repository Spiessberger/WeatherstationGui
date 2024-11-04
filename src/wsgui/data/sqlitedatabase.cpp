#include "sqlitedatabase.h"

#include <QLoggingCategory>
#include <QSqlError>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui.data.SQLiteDatabase")
}

namespace wsgui
{
namespace data
{

SQLiteDatabase::SQLiteDatabase()
    : m_database(QSqlDatabase::addDatabase("QSQLITE"))
{
}

bool SQLiteDatabase::initialize(const QString& fileName)
{
  m_database.setDatabaseName(fileName);
  if (!m_database.open())
  {
    qCWarning(log) << "failed to open database:" << m_database.lastError().text();
    return false;
  }
  return true;
}

QSqlQuery SQLiteDatabase::query()
{
  return QSqlQuery{m_database};
}

} // namespace data
} // namespace wsgui
