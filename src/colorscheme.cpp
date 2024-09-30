#include "colorscheme.h"

namespace wsgui
{
namespace colors
{

ColorScheme::ColorScheme(QObject* parent)
    : QObject{parent}
{
}

const ColorSchemeData& ColorScheme::colors() const
{
  return m_colors;
}

void ColorScheme::setColors(const ColorSchemeData& colors)
{
  m_colors = colors;
  emit colorsChanged();
}

QColor ColorScheme::primaryPaletteKeyColor() const
{
  return m_colors.primaryPaletteKeyColor;
}

void ColorScheme::setPrimaryPaletteKeyColor(const QColor& newPrimaryPaletteKeyColor)
{
  if (m_colors.primaryPaletteKeyColor == newPrimaryPaletteKeyColor)
    return;
  m_colors.primaryPaletteKeyColor = newPrimaryPaletteKeyColor;
  emit colorsChanged();
}

QColor ColorScheme::secondaryPaletteKeyColor() const
{
  return m_colors.secondaryPaletteKeyColor;
}

void ColorScheme::setSecondaryPaletteKeyColor(const QColor& newSecondaryPaletteKeyColor)
{
  if (m_colors.secondaryPaletteKeyColor == newSecondaryPaletteKeyColor)
    return;
  m_colors.secondaryPaletteKeyColor = newSecondaryPaletteKeyColor;
  emit colorsChanged();
}

QColor ColorScheme::tertiaryPaletteKeyColor() const
{
  return m_colors.tertiaryPaletteKeyColor;
}

void ColorScheme::setTertiaryPaletteKeyColor(const QColor& newTertiaryPaletteKeyColor)
{
  if (m_colors.tertiaryPaletteKeyColor == newTertiaryPaletteKeyColor)
    return;
  m_colors.tertiaryPaletteKeyColor = newTertiaryPaletteKeyColor;
  emit colorsChanged();
}

QColor ColorScheme::neutralPaletteKeyColor() const
{
  return m_colors.neutralPaletteKeyColor;
}

void ColorScheme::setNeutralPaletteKeyColor(const QColor& newNeutralPaletteKeyColor)
{
  if (m_colors.neutralPaletteKeyColor == newNeutralPaletteKeyColor)
    return;
  m_colors.neutralPaletteKeyColor = newNeutralPaletteKeyColor;
  emit colorsChanged();
}

QColor ColorScheme::neutralVariantPaletteKeyColor() const
{
  return m_colors.neutralVariantPaletteKeyColor;
}

void ColorScheme::setNeutralVariantPaletteKeyColor(const QColor& newNeutralVariantPaletteKeyColor)
{
  if (m_colors.neutralVariantPaletteKeyColor == newNeutralVariantPaletteKeyColor)
    return;
  m_colors.neutralVariantPaletteKeyColor = newNeutralVariantPaletteKeyColor;
  emit colorsChanged();
}

QColor ColorScheme::background() const
{
  return m_colors.background;
}

void ColorScheme::setBackground(const QColor& newBackground)
{
  if (m_colors.background == newBackground)
    return;
  m_colors.background = newBackground;
  emit colorsChanged();
}

QColor ColorScheme::onBackground() const
{
  return m_colors.onBackground;
}

void ColorScheme::setOnBackground(const QColor& newOnBackground)
{
  if (m_colors.onBackground == newOnBackground)
    return;
  m_colors.onBackground = newOnBackground;
  emit colorsChanged();
}

QColor ColorScheme::surface() const
{
  return m_colors.surface;
}

void ColorScheme::setSurface(const QColor& newSurface)
{
  if (m_colors.surface == newSurface)
    return;
  m_colors.surface = newSurface;
  emit colorsChanged();
}

QColor ColorScheme::surfaceDim() const
{
  return m_colors.surfaceDim;
}

void ColorScheme::setSurfaceDim(const QColor& newSurfaceDim)
{
  if (m_colors.surfaceDim == newSurfaceDim)
    return;
  m_colors.surfaceDim = newSurfaceDim;
  emit colorsChanged();
}

QColor ColorScheme::surfaceBright() const
{
  return m_colors.surfaceBright;
}

void ColorScheme::setSurfaceBright(const QColor& newSurfaceBright)
{
  if (m_colors.surfaceBright == newSurfaceBright)
    return;
  m_colors.surfaceBright = newSurfaceBright;
  emit colorsChanged();
}

QColor ColorScheme::surfaceContainerLowest() const
{
  return m_colors.surfaceContainerLowest;
}

void ColorScheme::setSurfaceContainerLowest(const QColor& newSurfaceContainerLowest)
{
  if (m_colors.surfaceContainerLowest == newSurfaceContainerLowest)
    return;
  m_colors.surfaceContainerLowest = newSurfaceContainerLowest;
  emit colorsChanged();
}

QColor ColorScheme::surfaceContainerLow() const
{
  return m_colors.surfaceContainerLow;
}

void ColorScheme::setSurfaceContainerLow(const QColor& newSurfaceContainerLow)
{
  if (m_colors.surfaceContainerLow == newSurfaceContainerLow)
    return;
  m_colors.surfaceContainerLow = newSurfaceContainerLow;
  emit colorsChanged();
}

QColor ColorScheme::surfaceContainer() const
{
  return m_colors.surfaceContainer;
}

void ColorScheme::setSurfaceContainer(const QColor& newSurfaceContainer)
{
  if (m_colors.surfaceContainer == newSurfaceContainer)
    return;
  m_colors.surfaceContainer = newSurfaceContainer;
  emit colorsChanged();
}

QColor ColorScheme::surfaceContainerHigh() const
{
  return m_colors.surfaceContainerHigh;
}

void ColorScheme::setSurfaceContainerHigh(const QColor& newSurfaceContainerHigh)
{
  if (m_colors.surfaceContainerHigh == newSurfaceContainerHigh)
    return;
  m_colors.surfaceContainerHigh = newSurfaceContainerHigh;
  emit colorsChanged();
}

QColor ColorScheme::surfaceContainerHighest() const
{
  return m_colors.surfaceContainerHighest;
}

void ColorScheme::setSurfaceContainerHighest(const QColor& newSurfaceContainerHighest)
{
  if (m_colors.surfaceContainerHighest == newSurfaceContainerHighest)
    return;
  m_colors.surfaceContainerHighest = newSurfaceContainerHighest;
  emit colorsChanged();
}

QColor ColorScheme::onSurface() const
{
  return m_colors.onSurface;
}

void ColorScheme::setOnSurface(const QColor& newOnSurface)
{
  if (m_colors.onSurface == newOnSurface)
    return;
  m_colors.onSurface = newOnSurface;
  emit colorsChanged();
}

QColor ColorScheme::surfaceVariant() const
{
  return m_colors.surfaceVariant;
}

void ColorScheme::setSurfaceVariant(const QColor& newSurfaceVariant)
{
  if (m_colors.surfaceVariant == newSurfaceVariant)
    return;
  m_colors.surfaceVariant = newSurfaceVariant;
  emit colorsChanged();
}

QColor ColorScheme::onSurfaceVariant() const
{
  return m_colors.onSurfaceVariant;
}

void ColorScheme::setOnSurfaceVariant(const QColor& newOnSurfaceVariant)
{
  if (m_colors.onSurfaceVariant == newOnSurfaceVariant)
    return;
  m_colors.onSurfaceVariant = newOnSurfaceVariant;
  emit colorsChanged();
}

QColor ColorScheme::inverseSurface() const
{
  return m_colors.inverseSurface;
}

void ColorScheme::setInverseSurface(const QColor& newInverseSurface)
{
  if (m_colors.inverseSurface == newInverseSurface)
    return;
  m_colors.inverseSurface = newInverseSurface;
  emit colorsChanged();
}

QColor ColorScheme::inverseOnSurface() const
{
  return m_colors.inverseOnSurface;
}

void ColorScheme::setInverseOnSurface(const QColor& newInverseOnSurface)
{
  if (m_colors.inverseOnSurface == newInverseOnSurface)
    return;
  m_colors.inverseOnSurface = newInverseOnSurface;
  emit colorsChanged();
}

QColor ColorScheme::outline() const
{
  return m_colors.outline;
}

void ColorScheme::setOutline(const QColor& newOutline)
{
  if (m_colors.outline == newOutline)
    return;
  m_colors.outline = newOutline;
  emit colorsChanged();
}

QColor ColorScheme::outlineVariant() const
{
  return m_colors.outlineVariant;
}

void ColorScheme::setOutlineVariant(const QColor& newOutlineVariant)
{
  if (m_colors.outlineVariant == newOutlineVariant)
    return;
  m_colors.outlineVariant = newOutlineVariant;
  emit colorsChanged();
}

QColor ColorScheme::shadow() const
{
  return m_colors.shadow;
}

void ColorScheme::setShadow(const QColor& newShadow)
{
  if (m_colors.shadow == newShadow)
    return;
  m_colors.shadow = newShadow;
  emit colorsChanged();
}

QColor ColorScheme::scrim() const
{
  return m_colors.scrim;
}

void ColorScheme::setScrim(const QColor& newScrim)
{
  if (m_colors.scrim == newScrim)
    return;
  m_colors.scrim = newScrim;
  emit colorsChanged();
}

QColor ColorScheme::surfaceTint() const
{
  return m_colors.surfaceTint;
}

void ColorScheme::setSurfaceTint(const QColor& newSurfaceTint)
{
  if (m_colors.surfaceTint == newSurfaceTint)
    return;
  m_colors.surfaceTint = newSurfaceTint;
  emit colorsChanged();
}

QColor ColorScheme::primary() const
{
  return m_colors.primary;
}

void ColorScheme::setPrimary(const QColor& newPrimary)
{
  if (m_colors.primary == newPrimary)
    return;
  m_colors.primary = newPrimary;
  emit colorsChanged();
}

QColor ColorScheme::onPrimary() const
{
  return m_colors.onPrimary;
}

void ColorScheme::setOnPrimary(const QColor& newOnPrimary)
{
  if (m_colors.onPrimary == newOnPrimary)
    return;
  m_colors.onPrimary = newOnPrimary;
  emit colorsChanged();
}

QColor ColorScheme::primaryContainer() const
{
  return m_colors.primaryContainer;
}

void ColorScheme::setPrimaryContainer(const QColor& newPrimaryContainer)
{
  if (m_colors.primaryContainer == newPrimaryContainer)
    return;
  m_colors.primaryContainer = newPrimaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::onPrimaryContainer() const
{
  return m_colors.onPrimaryContainer;
}

void ColorScheme::setOnPrimaryContainer(const QColor& newOnPrimaryContainer)
{
  if (m_colors.onPrimaryContainer == newOnPrimaryContainer)
    return;
  m_colors.onPrimaryContainer = newOnPrimaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::inversePrimary() const
{
  return m_colors.inversePrimary;
}

void ColorScheme::setInversePrimary(const QColor& newInversePrimary)
{
  if (m_colors.inversePrimary == newInversePrimary)
    return;
  m_colors.inversePrimary = newInversePrimary;
  emit colorsChanged();
}

QColor ColorScheme::secondary() const
{
  return m_colors.secondary;
}

void ColorScheme::setSecondary(const QColor& newSecondary)
{
  if (m_colors.secondary == newSecondary)
    return;
  m_colors.secondary = newSecondary;
  emit colorsChanged();
}

QColor ColorScheme::onSecondary() const
{
  return m_colors.onSecondary;
}

void ColorScheme::setOnSecondary(const QColor& newOnSecondary)
{
  if (m_colors.onSecondary == newOnSecondary)
    return;
  m_colors.onSecondary = newOnSecondary;
  emit colorsChanged();
}

QColor ColorScheme::secondaryContainer() const
{
  return m_colors.secondaryContainer;
}

void ColorScheme::setSecondaryContainer(const QColor& newSecondaryContainer)
{
  if (m_colors.secondaryContainer == newSecondaryContainer)
    return;
  m_colors.secondaryContainer = newSecondaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::onSecondaryContainer() const
{
  return m_colors.onSecondaryContainer;
}

void ColorScheme::setOnSecondaryContainer(const QColor& newOnSecondaryContainer)
{
  if (m_colors.onSecondaryContainer == newOnSecondaryContainer)
    return;
  m_colors.onSecondaryContainer = newOnSecondaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::tertiary() const
{
  return m_colors.tertiary;
}

void ColorScheme::setTertiary(const QColor& newTertiary)
{
  if (m_colors.tertiary == newTertiary)
    return;
  m_colors.tertiary = newTertiary;
  emit colorsChanged();
}

QColor ColorScheme::onTertiary() const
{
  return m_colors.onTertiary;
}

void ColorScheme::setOnTertiary(const QColor& newOnTertiary)
{
  if (m_colors.onTertiary == newOnTertiary)
    return;
  m_colors.onTertiary = newOnTertiary;
  emit colorsChanged();
}

QColor ColorScheme::tertiaryContainer() const
{
  return m_colors.tertiaryContainer;
}

void ColorScheme::setTertiaryContainer(const QColor& newTertiaryContainer)
{
  if (m_colors.tertiaryContainer == newTertiaryContainer)
    return;
  m_colors.tertiaryContainer = newTertiaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::onTertiaryContainer() const
{
  return m_colors.onTertiaryContainer;
}

void ColorScheme::setOnTertiaryContainer(const QColor& newOnTertiaryContainer)
{
  if (m_colors.onTertiaryContainer == newOnTertiaryContainer)
    return;
  m_colors.onTertiaryContainer = newOnTertiaryContainer;
  emit colorsChanged();
}

QColor ColorScheme::error() const
{
  return m_colors.error;
}

void ColorScheme::setError(const QColor& newError)
{
  if (m_colors.error == newError)
    return;
  m_colors.error = newError;
  emit colorsChanged();
}

QColor ColorScheme::onError() const
{
  return m_colors.onError;
}

void ColorScheme::setOnError(const QColor& newOnError)
{
  if (m_colors.onError == newOnError)
    return;
  m_colors.onError = newOnError;
  emit colorsChanged();
}

QColor ColorScheme::errorContainer() const
{
  return m_colors.errorContainer;
}

void ColorScheme::setErrorContainer(const QColor& newErrorContainer)
{
  if (m_colors.errorContainer == newErrorContainer)
    return;
  m_colors.errorContainer = newErrorContainer;
  emit colorsChanged();
}

QColor ColorScheme::onErrorContainer() const
{
  return m_colors.onErrorContainer;
}

void ColorScheme::setOnErrorContainer(const QColor& newOnErrorContainer)
{
  if (m_colors.onErrorContainer == newOnErrorContainer)
    return;
  m_colors.onErrorContainer = newOnErrorContainer;
  emit colorsChanged();
}

QColor ColorScheme::primaryFixed() const
{
  return m_colors.primaryFixed;
}

void ColorScheme::setPrimaryFixed(const QColor& newPrimaryFixed)
{
  if (m_colors.primaryFixed == newPrimaryFixed)
    return;
  m_colors.primaryFixed = newPrimaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::primaryFixedDim() const
{
  return m_colors.primaryFixedDim;
}

void ColorScheme::setPrimaryFixedDim(const QColor& newPrimaryFixedDim)
{
  if (m_colors.primaryFixedDim == newPrimaryFixedDim)
    return;
  m_colors.primaryFixedDim = newPrimaryFixedDim;
  emit colorsChanged();
}

QColor ColorScheme::onPrimaryFixed() const
{
  return m_colors.onPrimaryFixed;
}

void ColorScheme::setOnPrimaryFixed(const QColor& newOnPrimaryFixed)
{
  if (m_colors.onPrimaryFixed == newOnPrimaryFixed)
    return;
  m_colors.onPrimaryFixed = newOnPrimaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::onPrimaryFixedVariant() const
{
  return m_colors.onPrimaryFixedVariant;
}

void ColorScheme::setOnPrimaryFixedVariant(const QColor& newOnPrimaryFixedVariant)
{
  if (m_colors.onPrimaryFixedVariant == newOnPrimaryFixedVariant)
    return;
  m_colors.onPrimaryFixedVariant = newOnPrimaryFixedVariant;
  emit colorsChanged();
}

QColor ColorScheme::secondaryFixed() const
{
  return m_colors.secondaryFixed;
}

void ColorScheme::setSecondaryFixed(const QColor& newSecondaryFixed)
{
  if (m_colors.secondaryFixed == newSecondaryFixed)
    return;
  m_colors.secondaryFixed = newSecondaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::secondaryFixedDim() const
{
  return m_colors.secondaryFixedDim;
}

void ColorScheme::setSecondaryFixedDim(const QColor& newSecondaryFixedDim)
{
  if (m_colors.secondaryFixedDim == newSecondaryFixedDim)
    return;
  m_colors.secondaryFixedDim = newSecondaryFixedDim;
  emit colorsChanged();
}

QColor ColorScheme::onSecondaryFixed() const
{
  return m_colors.onSecondaryFixed;
}

void ColorScheme::setOnSecondaryFixed(const QColor& newOnSecondaryFixed)
{
  if (m_colors.onSecondaryFixed == newOnSecondaryFixed)
    return;
  m_colors.onSecondaryFixed = newOnSecondaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::onSecondaryFixedVariant() const
{
  return m_colors.onSecondaryFixedVariant;
}

void ColorScheme::setOnSecondaryFixedVariant(const QColor& newOnSecondaryFixedVariant)
{
  if (m_colors.onSecondaryFixedVariant == newOnSecondaryFixedVariant)
    return;
  m_colors.onSecondaryFixedVariant = newOnSecondaryFixedVariant;
  emit colorsChanged();
}

QColor ColorScheme::tertiaryFixed() const
{
  return m_colors.tertiaryFixed;
}

void ColorScheme::setTertiaryFixed(const QColor& newTertiaryFixed)
{
  if (m_colors.tertiaryFixed == newTertiaryFixed)
    return;
  m_colors.tertiaryFixed = newTertiaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::tertiaryFixedDim() const
{
  return m_colors.tertiaryFixedDim;
}

void ColorScheme::setTertiaryFixedDim(const QColor& newTertiaryFixedDim)
{
  if (m_colors.tertiaryFixedDim == newTertiaryFixedDim)
    return;
  m_colors.tertiaryFixedDim = newTertiaryFixedDim;
  emit colorsChanged();
}

QColor ColorScheme::onTertiaryFixed() const
{
  return m_colors.onTertiaryFixed;
}

void ColorScheme::setOnTertiaryFixed(const QColor& newOnTertiaryFixed)
{
  if (m_colors.onTertiaryFixed == newOnTertiaryFixed)
    return;
  m_colors.onTertiaryFixed = newOnTertiaryFixed;
  emit colorsChanged();
}

QColor ColorScheme::onTertiaryFixedVariant() const
{
  return m_colors.onTertiaryFixedVariant;
}

void ColorScheme::setOnTertiaryFixedVariant(const QColor& newOnTertiaryFixedVariant)
{
  if (m_colors.onTertiaryFixedVariant == newOnTertiaryFixedVariant)
    return;
  m_colors.onTertiaryFixedVariant = newOnTertiaryFixedVariant;
  emit colorsChanged();
}

} // namespace colors
} // namespace wsgui
