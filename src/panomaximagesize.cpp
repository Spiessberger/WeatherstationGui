#include "panomaximagesize.h"

namespace wsgui {
namespace panomax {

const std::vector<std::pair<PanomaxImageSize::Resolution, QString>> PanomaxImageSize::m_resolutionStrings = {
    {PanomaxImageSize::Optimized, "optimized"},
    {PanomaxImageSize::Hd, "hd"},
    {PanomaxImageSize::Full, "full"},
    {PanomaxImageSize::Original, "original"},
    {PanomaxImageSize::Reduced, "reduced"},
    {PanomaxImageSize::Small, "small"},
    {PanomaxImageSize::Thumb, "thumb"},
    {PanomaxImageSize::Default, "default"}};

QString PanomaxImageSize::resolutionToString(Resolution resolution)
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

PanomaxImageSize::Resolution PanomaxImageSize::stringToResolution(const QString& resolutionString)
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

PanomaxImageSize::Resolution PanomaxImageSize::resolution() const
{
  return m_resolution;
}

void PanomaxImageSize::setResolution(Resolution newResolution)
{
  if (m_resolution == newResolution)
  {
    return;
  }
  m_resolution = newResolution;
  emit resolutionChanged();
}

int PanomaxImageSize::numTiles() const
{
  return m_numTiles;
}

void PanomaxImageSize::setNumTiles(int newNumTiles)
{
  if (m_numTiles == newNumTiles)
  {
    return;
  }
  m_numTiles = newNumTiles;
  emit numTilesChanged();
}

} // namespace panomax
} // namespace wsgui
