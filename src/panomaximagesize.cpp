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
  m_resolution = newResolution;
}

int PanomaxImageSize::numTiles() const
{
  return m_numTiles;
}

void PanomaxImageSize::setNumTiles(int newNumTiles)
{
  m_numTiles = newNumTiles;
}

} // namespace panomax
} // namespace wsgui
