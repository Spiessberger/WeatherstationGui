#pragma once

#include "sqlitedatabase.h"
#include "weatherdatadao.h"

namespace wsgui
{
namespace data
{

class SQLiteWeatherDataDAO : public WeatherDataDAO
{
public:
  SQLiteWeatherDataDAO(SQLiteDatabase& database);

  bool initialize() override;
  bool insert(const WeatherData& weatherData) override;
  std::vector<WeatherData> getData(const QDateTime& from, const QDateTime& to) override;
  int numEntries(const QDateTime& from, const QDateTime& to) override;

private:
  SQLiteDatabase& m_database;
};

} // namespace data
} // namespace wsgui
