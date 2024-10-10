#pragma once

#include <nlohmann/json.hpp>

#include "imageresolution.h"

namespace wsgui
{
namespace panomax
{

NLOHMANN_JSON_SERIALIZE_ENUM(ImageResolution,
                             {{panomax::ImageResolution::None, nullptr},
                              {panomax::ImageResolution::Optimized, "optimized"},
                              {panomax::ImageResolution::Hd, "hd"},
                              {panomax::ImageResolution::Full, "full"},
                              {panomax::ImageResolution::Original, "original"},
                              {panomax::ImageResolution::Reduced, "reduced"},
                              {panomax::ImageResolution::Small, "small"},
                              {panomax::ImageResolution::Thumb, "thumb"},
                              {panomax::ImageResolution::Default, "default"}});

}
} // namespace wsgui
