#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

namespace wsgui
{
namespace data
{

class SQLiteDatabase
{
public:
  SQLiteDatabase();

  bool initialize(const QString& fileName);
  QSqlQuery query();

private:
  QSqlDatabase m_database;
};

} // namespace data
} // namespace wsgui
