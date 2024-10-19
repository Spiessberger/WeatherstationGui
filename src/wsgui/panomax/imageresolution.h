#pragma once

#include <QObject>
#include <QQmlEngine>

namespace wsgui
{
namespace panomax
{

class EnumImageResolution : public QObject
{
  Q_OBJECT
  QML_NAMED_ELEMENT(ImageResolution)
  QML_UNCREATABLE("Enum Namespace")
public:
  enum class Enum
  {
    None,
    Optimized,
    Hd,
    Full,
    Original,
    Reduced,
    Small,
    Thumb,
    Default
  };
  Q_ENUM(Enum)
};

using ImageResolution = EnumImageResolution::Enum;

} // namespace panomax
} // namespace wsgui

Q_DECLARE_METATYPE(wsgui::panomax::ImageResolution)
