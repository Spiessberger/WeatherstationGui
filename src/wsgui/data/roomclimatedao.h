#pragma once

#include "roomclimatedata.h"

namespace wsgui
{
namespace data
{

class RoomClimateDAO
{
public:
  virtual bool initialize() = 0;
  virtual bool insert(const RoomClimateData& roomClimateData) = 0;
  virtual std::vector<RoomClimateData> getData(const QDateTime& from = {},
                                               const QDateTime& to = {}) = 0;
  virtual int numEntries(const QDateTime& from = {}, const QDateTime& to = {}) = 0;
};

} // namespace data
} // namespace wsgui
