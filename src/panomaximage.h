#pragma once

#include <QObject>

#include <vector>

namespace wsgui {
namespace panomax {

class PanomaxImage : public QObject
{
  Q_OBJECT
public:
  enum Resolution { None, Optimized, Hd, Full, Original, Reduced, Small, Thumb, Default };
  Q_ENUM(Resolution)

  explicit PanomaxImage(QObject* parent = nullptr);

  static QString resolutionToString(Resolution resolution);
  static Resolution stringToResolution(const QString& resolutionString);

signals:

private:
  static const std::vector<std::pair<Resolution, QString>> m_resolutionStrings;
};

} // namespace panomax
} // namespace wsgui
