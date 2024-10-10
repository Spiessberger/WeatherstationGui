#pragma once

#include <QColor>

namespace wsgui
{
namespace colors
{

struct ColorSchemeData
{
  QColor primaryPaletteKeyColor;
  QColor secondaryPaletteKeyColor;
  QColor tertiaryPaletteKeyColor;
  QColor neutralPaletteKeyColor;
  QColor neutralVariantPaletteKeyColor;
  QColor background;
  QColor onBackground;
  QColor surface;
  QColor surfaceDim;
  QColor surfaceBright;
  QColor surfaceContainerLowest;
  QColor surfaceContainerLow;
  QColor surfaceContainer;
  QColor surfaceContainerHigh;
  QColor surfaceContainerHighest;
  QColor onSurface;
  QColor surfaceVariant;
  QColor onSurfaceVariant;
  QColor inverseSurface;
  QColor inverseOnSurface;
  QColor outline;
  QColor outlineVariant;
  QColor shadow;
  QColor scrim;
  QColor surfaceTint;
  QColor primary;
  QColor onPrimary;
  QColor primaryContainer;
  QColor onPrimaryContainer;
  QColor inversePrimary;
  QColor secondary;
  QColor onSecondary;
  QColor secondaryContainer;
  QColor onSecondaryContainer;
  QColor tertiary;
  QColor onTertiary;
  QColor tertiaryContainer;
  QColor onTertiaryContainer;
  QColor error;
  QColor onError;
  QColor errorContainer;
  QColor onErrorContainer;
  QColor primaryFixed;
  QColor primaryFixedDim;
  QColor onPrimaryFixed;
  QColor onPrimaryFixedVariant;
  QColor secondaryFixed;
  QColor secondaryFixedDim;
  QColor onSecondaryFixed;
  QColor onSecondaryFixedVariant;
  QColor tertiaryFixed;
  QColor tertiaryFixedDim;
  QColor onTertiaryFixed;
  QColor onTertiaryFixedVariant;
};

} // namespace colors
} // namespace wsgui
