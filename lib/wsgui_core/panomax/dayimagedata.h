#pragma once

#include <QDate>
#include <QTime>
#include <string>
#include <vector>

namespace wsgui::core::panomax
{

struct ImageSize
{
  std::string resolution;
  int rows = 0;
  int cols = 0;
  int tileWidth = 0;
  int tileHeight = 0;
};

struct ImageData
{
  QTime time;
};

struct DayImageData
{
  int camId = 0;
  QDate date;
  std::vector<ImageSize> sizes;
  std::vector<ImageData> images;
};

} // namespace wsgui::core::panomax
