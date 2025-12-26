#include "colorscheme.h"

void ColorScheme::setColorScheme(
    const material_color_utilities::DynamicScheme& colorScheme)
{
  m_colorScheme = colorScheme;
  emit colorSchemeChanged();
}

QColor ColorScheme::primaryPaletteKeyColor() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetPrimaryPaletteKeyColor());
  }
  return {};
}

QColor ColorScheme::secondaryPaletteKeyColor() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSecondaryPaletteKeyColor());
  }
  return {};
}

QColor ColorScheme::tertiaryPaletteKeyColor() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetTertiaryPaletteKeyColor());
  }
  return {};
}

QColor ColorScheme::neutralPaletteKeyColor() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetNeutralPaletteKeyColor());
  }
  return {};
}

QColor ColorScheme::neutralVariantPaletteKeyColor() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetNeutralVariantPaletteKeyColor());
  }
  return {};
}

QColor ColorScheme::background() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetBackground());
  }
  return {};
}

QColor ColorScheme::onBackground() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnBackground());
  }
  return {};
}

QColor ColorScheme::surface() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurface());
  }
  return {};
}

QColor ColorScheme::surfaceDim() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceDim());
  }
  return {};
}

QColor ColorScheme::surfaceBright() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceBright());
  }
  return {};
}

QColor ColorScheme::surfaceContainerLowest() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceContainerLowest());
  }
  return {};
}

QColor ColorScheme::surfaceContainerLow() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceContainerLow());
  }
  return {};
}

QColor ColorScheme::surfaceContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceContainer());
  }
  return {};
}

QColor ColorScheme::surfaceContainerHigh() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceContainerHigh());
  }
  return {};
}

QColor ColorScheme::surfaceContainerHighest() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceContainerHighest());
  }
  return {};
}

QColor ColorScheme::onSurface() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSurface());
  }
  return {};
}

QColor ColorScheme::surfaceVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceVariant());
  }
  return {};
}

QColor ColorScheme::onSurfaceVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSurfaceVariant());
  }
  return {};
}

QColor ColorScheme::inverseSurface() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetInverseSurface());
  }
  return {};
}

QColor ColorScheme::inverseOnSurface() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetInverseOnSurface());
  }
  return {};
}

QColor ColorScheme::outline() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOutline());
  }
  return {};
}

QColor ColorScheme::outlineVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOutlineVariant());
  }
  return {};
}

QColor ColorScheme::shadow() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetShadow());
  }
  return {};
}

QColor ColorScheme::scrim() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetScrim());
  }
  return {};
}

QColor ColorScheme::surfaceTint() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSurfaceTint());
  }
  return {};
}

QColor ColorScheme::primary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetPrimary());
  }
  return {};
}

QColor ColorScheme::onPrimary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnPrimary());
  }
  return {};
}

QColor ColorScheme::primaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetPrimaryContainer());
  }
  return {};
}

QColor ColorScheme::onPrimaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnPrimaryContainer());
  }
  return {};
}

QColor ColorScheme::inversePrimary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetInversePrimary());
  }
  return {};
}

QColor ColorScheme::secondary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSecondary());
  }
  return {};
}

QColor ColorScheme::onSecondary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSecondary());
  }
  return {};
}

QColor ColorScheme::secondaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSecondaryContainer());
  }
  return {};
}

QColor ColorScheme::onSecondaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSecondaryContainer());
  }
  return {};
}

QColor ColorScheme::tertiary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetTertiary());
  }
  return {};
}

QColor ColorScheme::onTertiary() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnTertiary());
  }
  return {};
}

QColor ColorScheme::tertiaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetTertiaryContainer());
  }
  return {};
}

QColor ColorScheme::onTertiaryContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnTertiaryContainer());
  }
  return {};
}

QColor ColorScheme::error() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetError());
  }
  return {};
}

QColor ColorScheme::onError() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnError());
  }
  return {};
}

QColor ColorScheme::errorContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetErrorContainer());
  }
  return {};
}

QColor ColorScheme::onErrorContainer() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnErrorContainer());
  }
  return {};
}

QColor ColorScheme::primaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetPrimaryFixed());
  }
  return {};
}

QColor ColorScheme::primaryFixedDim() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetPrimaryFixedDim());
  }
  return {};
}

QColor ColorScheme::onPrimaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnPrimaryFixed());
  }
  return {};
}

QColor ColorScheme::onPrimaryFixedVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnPrimaryFixedVariant());
  }
  return {};
}

QColor ColorScheme::secondaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSecondaryFixed());
  }
  return {};
}

QColor ColorScheme::secondaryFixedDim() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetSecondaryFixedDim());
  }
  return {};
}

QColor ColorScheme::onSecondaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSecondaryFixed());
  }
  return {};
}

QColor ColorScheme::onSecondaryFixedVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnSecondaryFixedVariant());
  }
  return {};
}

QColor ColorScheme::tertiaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetTertiaryFixed());
  }
  return {};
}

QColor ColorScheme::tertiaryFixedDim() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetTertiaryFixedDim());
  }
  return {};
}

QColor ColorScheme::onTertiaryFixed() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnTertiaryFixed());
  }
  return {};
}

QColor ColorScheme::onTertiaryFixedVariant() const
{
  if (m_colorScheme)
  {
    return QColor::fromRgb(m_colorScheme->GetOnTertiaryFixedVariant());
  }
  return {};
}
