#pragma once

#include "roomclimatedao.h"
#include "sqlitedatabase.h"

namespace wsgui
{
namespace data
{

class SQLiteRoomClimateDAO : public RoomClimateDAO
{
public:
  SQLiteRoomClimateDAO(SQLiteDatabase& database);

  bool initialize() override;
  bool insert(const RoomClimateData& roomClimateData) override;
  std::vector<RoomClimateData> getData(const QDateTime& from, const QDateTime& to) override;
  int numEntries(const QDateTime& from, const QDateTime& to) override;

private:
  SQLiteDatabase& m_database;
};

} // namespace data
} // namespace wsgui
