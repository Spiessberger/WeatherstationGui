#include "panomaximage.h"

namespace wsgui {
namespace panomax {

const std::vector<std::pair<PanomaxImage::Resolution, QString>> PanomaxImage::m_resolutionStrings = {
    {PanomaxImage::Optimized, "optimized"},
    {PanomaxImage::Hd, "hd"},
    {PanomaxImage::Full, "full"},
    {PanomaxImage::Original, "original"},
    {PanomaxImage::Reduced, "reduced"},
    {PanomaxImage::Small, "small"},
    {PanomaxImage::Thumb, "thumb"},
    {PanomaxImage::Default, "default"}};

PanomaxImage::PanomaxImage(QObject* parent) : QObject{parent}
{
}

QString PanomaxImage::resolutionToString(Resolution resolution)
{
  for (const auto& pair : m_resolutionStrings)
  {
    if (pair.first == resolution)
    {
      return pair.second;
    }
  }
  return QString{};
}

PanomaxImage::Resolution PanomaxImage::stringToResolution(const QString& resolutionString)
{
  for (const auto& pair : m_resolutionStrings)
  {
    if (pair.second == resolutionString)
    {
      return pair.first;
    }
  }
  return Resolution::None;
}

} // namespace panomax
} // namespace wsgui
