#pragma once

#include <QObject>
#include <QQmlEngine>

#include "colorschemedata.h"

namespace wsgui
{
namespace colors
{

class ColorScheme : public QObject
{
  Q_OBJECT
  // clang-format off
  Q_PROPERTY(QColor primaryPaletteKeyColor READ primaryPaletteKeyColor WRITE setPrimaryPaletteKeyColor NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor secondaryPaletteKeyColor READ secondaryPaletteKeyColor WRITE setSecondaryPaletteKeyColor NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor tertiaryPaletteKeyColor READ tertiaryPaletteKeyColor WRITE setTertiaryPaletteKeyColor NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor neutralPaletteKeyColor READ neutralPaletteKeyColor WRITE setNeutralPaletteKeyColor NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor neutralVariantPaletteKeyColor READ neutralVariantPaletteKeyColor WRITE setNeutralVariantPaletteKeyColor NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onBackground READ onBackground WRITE setOnBackground NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surface READ surface WRITE setSurface NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceDim READ surfaceDim WRITE setSurfaceDim NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceBright READ surfaceBright WRITE setSurfaceBright NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerLowest READ surfaceContainerLowest WRITE setSurfaceContainerLowest NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerLow READ surfaceContainerLow WRITE setSurfaceContainerLow NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceContainer READ surfaceContainer WRITE setSurfaceContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerHigh READ surfaceContainerHigh WRITE setSurfaceContainerHigh NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerHighest READ surfaceContainerHighest WRITE setSurfaceContainerHighest NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSurface READ onSurface WRITE setOnSurface NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceVariant READ surfaceVariant WRITE setSurfaceVariant NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSurfaceVariant READ onSurfaceVariant WRITE setOnSurfaceVariant NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor inverseSurface READ inverseSurface WRITE setInverseSurface NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor inverseOnSurface READ inverseOnSurface WRITE setInverseOnSurface NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor outline READ outline WRITE setOutline NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor outlineVariant READ outlineVariant WRITE setOutlineVariant NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor shadow READ shadow WRITE setShadow NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor scrim READ scrim WRITE setScrim NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor surfaceTint READ surfaceTint WRITE setSurfaceTint NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor primary READ primary WRITE setPrimary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onPrimary READ onPrimary WRITE setOnPrimary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor primaryContainer READ primaryContainer WRITE setPrimaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onPrimaryContainer READ onPrimaryContainer WRITE setOnPrimaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor inversePrimary READ inversePrimary WRITE setInversePrimary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor secondary READ secondary WRITE setSecondary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSecondary READ onSecondary WRITE setOnSecondary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor secondaryContainer READ secondaryContainer WRITE setSecondaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSecondaryContainer READ onSecondaryContainer WRITE setOnSecondaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor tertiary READ tertiary WRITE setTertiary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onTertiary READ onTertiary WRITE setOnTertiary NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor tertiaryContainer READ tertiaryContainer WRITE setTertiaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onTertiaryContainer READ onTertiaryContainer WRITE setOnTertiaryContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor error READ error WRITE setError NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onError READ onError WRITE setOnError NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor errorContainer READ errorContainer WRITE setErrorContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onErrorContainer READ onErrorContainer WRITE setOnErrorContainer NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor primaryFixed READ primaryFixed WRITE setPrimaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor primaryFixedDim READ primaryFixedDim WRITE setPrimaryFixedDim NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onPrimaryFixed READ onPrimaryFixed WRITE setOnPrimaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onPrimaryFixedVariant READ onPrimaryFixedVariant WRITE setOnPrimaryFixedVariant NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor secondaryFixed READ secondaryFixed WRITE setSecondaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor secondaryFixedDim READ secondaryFixedDim WRITE setSecondaryFixedDim NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSecondaryFixed READ onSecondaryFixed WRITE setOnSecondaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onSecondaryFixedVariant READ onSecondaryFixedVariant WRITE setOnSecondaryFixedVariant NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor tertiaryFixed READ tertiaryFixed WRITE setTertiaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor tertiaryFixedDim READ tertiaryFixedDim WRITE setTertiaryFixedDim NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onTertiaryFixed READ onTertiaryFixed WRITE setOnTertiaryFixed NOTIFY colorsChanged FINAL)
  Q_PROPERTY(QColor onTertiaryFixedVariant READ onTertiaryFixedVariant WRITE setOnTertiaryFixedVariant NOTIFY colorsChanged FINAL)
  // clang-format on
  QML_ELEMENT
public:
  explicit ColorScheme(QObject* parent = nullptr);

  const ColorSchemeData& colors() const;
  void setColors(const ColorSchemeData& colors);

  QColor primaryPaletteKeyColor() const;
  void setPrimaryPaletteKeyColor(const QColor& newPrimaryPaletteKeyColor);

  QColor secondaryPaletteKeyColor() const;
  void setSecondaryPaletteKeyColor(const QColor& newSecondaryPaletteKeyColor);

  QColor tertiaryPaletteKeyColor() const;
  void setTertiaryPaletteKeyColor(const QColor& newTertiaryPaletteKeyColor);

  QColor neutralPaletteKeyColor() const;
  void setNeutralPaletteKeyColor(const QColor& newNeutralPaletteKeyColor);

  QColor neutralVariantPaletteKeyColor() const;
  void setNeutralVariantPaletteKeyColor(const QColor& newNeutralVariantPaletteKeyColor);

  QColor background() const;
  void setBackground(const QColor& newBackground);

  QColor onBackground() const;
  void setOnBackground(const QColor& newOnBackground);

  QColor surface() const;
  void setSurface(const QColor& newSurface);

  QColor surfaceDim() const;
  void setSurfaceDim(const QColor& newSurfaceDim);

  QColor surfaceBright() const;
  void setSurfaceBright(const QColor& newSurfaceBright);

  QColor surfaceContainerLowest() const;
  void setSurfaceContainerLowest(const QColor& newSurfaceContainerLowest);

  QColor surfaceContainerLow() const;
  void setSurfaceContainerLow(const QColor& newSurfaceContainerLow);

  QColor surfaceContainer() const;
  void setSurfaceContainer(const QColor& newSurfaceContainer);

  QColor surfaceContainerHigh() const;
  void setSurfaceContainerHigh(const QColor& newSurfaceContainerHigh);

  QColor surfaceContainerHighest() const;
  void setSurfaceContainerHighest(const QColor& newSurfaceContainerHighest);

  QColor onSurface() const;
  void setOnSurface(const QColor& newOnSurface);

  QColor surfaceVariant() const;
  void setSurfaceVariant(const QColor& newSurfaceVariant);

  QColor onSurfaceVariant() const;
  void setOnSurfaceVariant(const QColor& newOnSurfaceVariant);

  QColor inverseSurface() const;
  void setInverseSurface(const QColor& newInverseSurface);

  QColor inverseOnSurface() const;
  void setInverseOnSurface(const QColor& newInverseOnSurface);

  QColor outline() const;
  void setOutline(const QColor& newOutline);

  QColor outlineVariant() const;
  void setOutlineVariant(const QColor& newOutlineVariant);

  QColor shadow() const;
  void setShadow(const QColor& newShadow);

  QColor scrim() const;
  void setScrim(const QColor& newScrim);

  QColor surfaceTint() const;
  void setSurfaceTint(const QColor& newSurfaceTint);

  QColor primary() const;
  void setPrimary(const QColor& newPrimary);

  QColor onPrimary() const;
  void setOnPrimary(const QColor& newOnPrimary);

  QColor primaryContainer() const;
  void setPrimaryContainer(const QColor& newPrimaryContainer);

  QColor onPrimaryContainer() const;
  void setOnPrimaryContainer(const QColor& newOnPrimaryContainer);

  QColor inversePrimary() const;
  void setInversePrimary(const QColor& newInversePrimary);

  QColor secondary() const;
  void setSecondary(const QColor& newSecondary);

  QColor onSecondary() const;
  void setOnSecondary(const QColor& newOnSecondary);

  QColor secondaryContainer() const;
  void setSecondaryContainer(const QColor& newSecondaryContainer);

  QColor onSecondaryContainer() const;
  void setOnSecondaryContainer(const QColor& newOnSecondaryContainer);

  QColor tertiary() const;
  void setTertiary(const QColor& newTertiary);

  QColor onTertiary() const;
  void setOnTertiary(const QColor& newOnTertiary);

  QColor tertiaryContainer() const;
  void setTertiaryContainer(const QColor& newTertiaryContainer);

  QColor onTertiaryContainer() const;
  void setOnTertiaryContainer(const QColor& newOnTertiaryContainer);

  QColor error() const;
  void setError(const QColor& newError);

  QColor onError() const;
  void setOnError(const QColor& newOnError);

  QColor errorContainer() const;
  void setErrorContainer(const QColor& newErrorContainer);

  QColor onErrorContainer() const;
  void setOnErrorContainer(const QColor& newOnErrorContainer);

  QColor primaryFixed() const;
  void setPrimaryFixed(const QColor& newPrimaryFixed);

  QColor primaryFixedDim() const;
  void setPrimaryFixedDim(const QColor& newPrimaryFixedDim);

  QColor onPrimaryFixed() const;
  void setOnPrimaryFixed(const QColor& newOnPrimaryFixed);

  QColor onPrimaryFixedVariant() const;
  void setOnPrimaryFixedVariant(const QColor& newOnPrimaryFixedVariant);

  QColor secondaryFixed() const;
  void setSecondaryFixed(const QColor& newSecondaryFixed);

  QColor secondaryFixedDim() const;
  void setSecondaryFixedDim(const QColor& newSecondaryFixedDim);

  QColor onSecondaryFixed() const;
  void setOnSecondaryFixed(const QColor& newOnSecondaryFixed);

  QColor onSecondaryFixedVariant() const;
  void setOnSecondaryFixedVariant(const QColor& newOnSecondaryFixedVariant);

  QColor tertiaryFixed() const;
  void setTertiaryFixed(const QColor& newTertiaryFixed);

  QColor tertiaryFixedDim() const;
  void setTertiaryFixedDim(const QColor& newTertiaryFixedDim);

  QColor onTertiaryFixed() const;
  void setOnTertiaryFixed(const QColor& newOnTertiaryFixed);

  QColor onTertiaryFixedVariant() const;
  void setOnTertiaryFixedVariant(const QColor& newOnTertiaryFixedVariant);

signals:
  void colorsChanged();

private:
  ColorSchemeData m_colors;
};

} // namespace colors
} // namespace wsgui
