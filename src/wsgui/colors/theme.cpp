#include "theme.h"

namespace wsgui
{
namespace colors
{

void Theme::updateThemeColors(const ColorScheme* const colorScheme)
{
  if (colorScheme == nullptr)
  {
    setColors(defaultColors());
  }
  else
  {
    setColors(colorScheme->colors());
  }
}

constexpr ColorSchemeData Theme::defaultColors()
{
  ColorSchemeData scheme;

  return scheme;
}

} // namespace colors
} // namespace wsgui
