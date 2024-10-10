#pragma once

#include "imageresolution.h"

namespace wsgui
{
namespace panomax
{

struct ImageSize
{
  int columns = 0;
  ImageResolution resolution = ImageResolution::None;

  bool operator==(const ImageSize& other) const = default;
};

} // namespace panomax
} // namespace wsgui
