#pragma once

#include <QDate>
#include <QTime>

#include <vector>

#include "imagesize.h"

namespace wsgui
{
namespace panomax
{

struct DayInfo
{
  QDate date;
  std::vector<ImageSize> imageSizes;
  std::vector<QTime> imageTimes;
};

} // namespace panomax
} // namespace wsgui
