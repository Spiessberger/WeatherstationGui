#pragma once

#include <QQmlEngine>

namespace wsgui {
namespace panomax {

class PanomaxImageSize
{
  Q_GADGET
  QML_ELEMENT
  QML_UNCREATABLE("Enum namespace")
public:
  enum Resolution { None, Optimized, Hd, Full, Original, Reduced, Small, Thumb, Default };
  Q_ENUM(Resolution)

  PanomaxImageSize() = default;

  static QString resolutionToString(Resolution resolution);
  static Resolution stringToResolution(const QString& resolutionString);

  Resolution resolution() const;
  void setResolution(Resolution newResolution);

  int numTiles() const;
  void setNumTiles(int newNumTiles);

  bool operator==(const PanomaxImageSize& other) const;

private:
  static const std::vector<std::pair<Resolution, QString>> m_resolutionStrings;
  Resolution m_resolution = Resolution::None;
  int m_numTiles = 0;
};

} // namespace panomax
} // namespace wsgui
