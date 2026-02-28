#include "colorscheme.h"

void ColorScheme::setColorScheme(
    const ColorSchemeData& colorScheme)
{
  m_colorScheme = colorScheme;
  emit colorSchemeChanged();
}

QColor ColorScheme::primaryPaletteKeyColor() const
{
  return m_colorScheme.primaryPaletteKeyColor;
}

QColor ColorScheme::secondaryPaletteKeyColor() const
{
  return m_colorScheme.secondaryPaletteKeyColor;
}

QColor ColorScheme::tertiaryPaletteKeyColor() const
{
  return m_colorScheme.tertiaryPaletteKeyColor;
}

QColor ColorScheme::neutralPaletteKeyColor() const
{
  return m_colorScheme.neutralPaletteKeyColor;
}

QColor ColorScheme::neutralVariantPaletteKeyColor() const
{
  return m_colorScheme.neutralVariantPaletteKeyColor;
}

QColor ColorScheme::background() const
{
  return m_colorScheme.background;
}

QColor ColorScheme::onBackground() const
{
  return m_colorScheme.onBackground;
}

QColor ColorScheme::surface() const
{
  return m_colorScheme.surface;
}

QColor ColorScheme::surfaceDim() const
{
  return m_colorScheme.surfaceDim;
}

QColor ColorScheme::surfaceBright() const
{
  return m_colorScheme.surfaceBright;
}

QColor ColorScheme::surfaceContainerLowest() const
{
  return m_colorScheme.surfaceContainerLowest;
}

QColor ColorScheme::surfaceContainerLow() const
{
  return m_colorScheme.surfaceContainerLow;
}

QColor ColorScheme::surfaceContainer() const
{
  return m_colorScheme.surfaceContainer;
}

QColor ColorScheme::surfaceContainerHigh() const
{
  return m_colorScheme.surfaceContainerHigh;
}

QColor ColorScheme::surfaceContainerHighest() const
{
  return m_colorScheme.surfaceContainerHighest;
}

QColor ColorScheme::onSurface() const
{
  return m_colorScheme.onSurface;
}

QColor ColorScheme::surfaceVariant() const
{
  return m_colorScheme.surfaceVariant;
}

QColor ColorScheme::onSurfaceVariant() const
{
  return m_colorScheme.onSurfaceVariant;
}

QColor ColorScheme::inverseSurface() const
{
  return m_colorScheme.inverseSurface;
}

QColor ColorScheme::inverseOnSurface() const
{
  return m_colorScheme.inverseOnSurface;
}

QColor ColorScheme::outline() const
{
  return m_colorScheme.outline;
}

QColor ColorScheme::outlineVariant() const
{
  return m_colorScheme.outlineVariant;
}

QColor ColorScheme::shadow() const
{
  return m_colorScheme.shadow;
}

QColor ColorScheme::scrim() const
{
  return m_colorScheme.scrim;
}

QColor ColorScheme::surfaceTint() const
{
  return m_colorScheme.surfaceTint;
}

QColor ColorScheme::primary() const
{
  return m_colorScheme.primary;
}

QColor ColorScheme::onPrimary() const
{
  return m_colorScheme.onPrimary;
}

QColor ColorScheme::primaryContainer() const
{
  return m_colorScheme.primaryContainer;
}

QColor ColorScheme::onPrimaryContainer() const
{
  return m_colorScheme.onPrimaryContainer;
}

QColor ColorScheme::inversePrimary() const
{
  return m_colorScheme.inversePrimary;
}

QColor ColorScheme::secondary() const
{
  return m_colorScheme.secondary;
}

QColor ColorScheme::onSecondary() const
{
  return m_colorScheme.onSecondary;
}

QColor ColorScheme::secondaryContainer() const
{
  return m_colorScheme.secondaryContainer;
}

QColor ColorScheme::onSecondaryContainer() const
{
  return m_colorScheme.onSecondaryContainer;
}

QColor ColorScheme::tertiary() const
{
  return m_colorScheme.tertiary;
}

QColor ColorScheme::onTertiary() const
{
  return m_colorScheme.onTertiary;
}

QColor ColorScheme::tertiaryContainer() const
{
  return m_colorScheme.tertiaryContainer;
}

QColor ColorScheme::onTertiaryContainer() const
{
  return m_colorScheme.onTertiaryContainer;
}

QColor ColorScheme::error() const
{
  return m_colorScheme.error;
}

QColor ColorScheme::onError() const
{
  return m_colorScheme.onError;
}

QColor ColorScheme::errorContainer() const
{
  return m_colorScheme.errorContainer;
}

QColor ColorScheme::onErrorContainer() const
{
  return m_colorScheme.onErrorContainer;
}

QColor ColorScheme::primaryFixed() const
{
  return m_colorScheme.primaryFixed;
}

QColor ColorScheme::primaryFixedDim() const
{
  return m_colorScheme.primaryFixedDim;
}

QColor ColorScheme::onPrimaryFixed() const
{
  return m_colorScheme.onPrimaryFixed;
}

QColor ColorScheme::onPrimaryFixedVariant() const
{
  return m_colorScheme.onPrimaryFixedVariant;
}

QColor ColorScheme::secondaryFixed() const
{
  return m_colorScheme.secondaryFixed;
}

QColor ColorScheme::secondaryFixedDim() const
{
  return m_colorScheme.secondaryFixedDim;
}

QColor ColorScheme::onSecondaryFixed() const
{
  return m_colorScheme.onSecondaryFixed;
}

QColor ColorScheme::onSecondaryFixedVariant() const
{
  return m_colorScheme.onSecondaryFixedVariant;
}

QColor ColorScheme::tertiaryFixed() const
{
  return m_colorScheme.tertiaryFixed;
}

QColor ColorScheme::tertiaryFixedDim() const
{
  return m_colorScheme.tertiaryFixedDim;
}

QColor ColorScheme::onTertiaryFixed() const
{
  return m_colorScheme.onTertiaryFixed;
}

QColor ColorScheme::onTertiaryFixedVariant() const
{
  return m_colorScheme.onTertiaryFixedVariant;
}
