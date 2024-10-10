#include <QString>

#pragma once

namespace wsgui {
namespace panomax {

enum class ImageResolution { None, Optimized, Hd, Full, Original, Reduced, Small, Thumb, Default };

static QString resolutionToString(ImageResolution resolution)
{
  switch (resolution)
  {
  case ImageResolution::Optimized:
    return QStringLiteral("Optimized");
  case ImageResolution::Hd:
    return QStringLiteral("Hd");
  case ImageResolution::Full:
    return QStringLiteral("Full");
  case ImageResolution::Original:
    return QStringLiteral("Original");
  case ImageResolution::Reduced:
    return QStringLiteral("Reduced");
  case ImageResolution::Small:
    return QStringLiteral("Small");
  case ImageResolution::Thumb:
    return QStringLiteral("Thumb");
  case ImageResolution::Default:
    return QStringLiteral("Default");
  default:
    return QStringLiteral("None");
  }
}
static ImageResolution stringToResolution(const QString& resolutionString)
{
  if (resolutionString == QStringLiteral("Optimized"))
    return ImageResolution::Optimized;
  if (resolutionString == QStringLiteral("Hd"))
    return ImageResolution::Hd;
  if (resolutionString == QStringLiteral("Full"))
    return ImageResolution::Full;
  if (resolutionString == QStringLiteral("Original"))
    return ImageResolution::Original;
  if (resolutionString == QStringLiteral("Reduced"))
    return ImageResolution::Reduced;
  if (resolutionString == QStringLiteral("Small"))
    return ImageResolution::Small;
  if (resolutionString == QStringLiteral("Thumb"))
    return ImageResolution::Thumb;
  if (resolutionString == QStringLiteral("Default"))
    return ImageResolution::Default;
  return ImageResolution::None;
}

} // namespace panomax
} // namespace wsgui
