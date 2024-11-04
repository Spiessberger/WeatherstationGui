#pragma once

#include "weatherdata.h"

namespace wsgui
{
namespace data
{

class WeatherDataDAO
{
public:
  virtual bool initialize() = 0;
  virtual bool insert(const WeatherData& weatherData) = 0;
  virtual std::vector<WeatherData> getData(const QDateTime& from = {},
                                           const QDateTime& to = {}) = 0;
  virtual int numEntries(const QDateTime& from = {}, const QDateTime& to = {}) = 0;
};

} // namespace data
} // namespace wsgui
