#pragma once

#include "colorscheme.h"
#include <QQmlEngine>

namespace wsgui
{
namespace colors
{

class Theme : public ColorScheme
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
public:
  Theme() = default;

  Q_INVOKABLE void updateThemeColors(const ColorScheme* const colorScheme);

  constexpr static ColorSchemeData defaultColors();
};

} // namespace colors
} // namespace wsgui
