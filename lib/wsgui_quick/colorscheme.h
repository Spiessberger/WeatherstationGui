#pragma once

#include <QColor>
#include <QObject>
#include <QQmlEngine>

#include <colorschemedata.h>

class ColorScheme : public QObject
{
  Q_OBJECT
  QML_ELEMENT

  // clang-format off
  Q_PROPERTY(QColor primaryPaletteKeyColor READ primaryPaletteKeyColor NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor secondaryPaletteKeyColor READ secondaryPaletteKeyColor NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor tertiaryPaletteKeyColor READ tertiaryPaletteKeyColor NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor neutralPaletteKeyColor READ neutralPaletteKeyColor NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor neutralVariantPaletteKeyColor READ neutralVariantPaletteKeyColor NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor background READ background NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onBackground READ onBackground NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surface READ surface NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceDim READ surfaceDim NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceBright READ surfaceBright NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerLowest READ surfaceContainerLowest NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerLow READ surfaceContainerLow NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceContainer READ surfaceContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerHigh READ surfaceContainerHigh NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceContainerHighest READ surfaceContainerHighest NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSurface READ onSurface NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceVariant READ surfaceVariant NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSurfaceVariant READ onSurfaceVariant NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor inverseSurface READ inverseSurface NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor inverseOnSurface READ inverseOnSurface NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor outline READ outline NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor outlineVariant READ outlineVariant NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor shadow READ shadow NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor scrim READ scrim NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor surfaceTint READ surfaceTint NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor primary READ primary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onPrimary READ onPrimary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor primaryContainer READ primaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onPrimaryContainer READ onPrimaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor inversePrimary READ inversePrimary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor secondary READ secondary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSecondary READ onSecondary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor secondaryContainer READ secondaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSecondaryContainer READ onSecondaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor tertiary READ tertiary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onTertiary READ onTertiary NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor tertiaryContainer READ tertiaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onTertiaryContainer READ onTertiaryContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor error READ error NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onError READ onError NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor errorContainer READ errorContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onErrorContainer READ onErrorContainer NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor primaryFixed READ primaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor primaryFixedDim READ primaryFixedDim NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onPrimaryFixed READ onPrimaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onPrimaryFixedVariant READ onPrimaryFixedVariant NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor secondaryFixed READ secondaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor secondaryFixedDim READ secondaryFixedDim NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSecondaryFixed READ onSecondaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onSecondaryFixedVariant READ onSecondaryFixedVariant NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor tertiaryFixed READ tertiaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor tertiaryFixedDim READ tertiaryFixedDim NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onTertiaryFixed READ onTertiaryFixed NOTIFY colorSchemeChanged FINAL)
  Q_PROPERTY(QColor onTertiaryFixedVariant READ onTertiaryFixedVariant NOTIFY colorSchemeChanged FINAL)
  // clang-format on
public:
  explicit ColorScheme() = default;

  void setColorScheme(const ColorSchemeData& colorScheme);

  QColor primaryPaletteKeyColor() const;
  QColor secondaryPaletteKeyColor() const;
  QColor tertiaryPaletteKeyColor() const;
  QColor neutralPaletteKeyColor() const;
  QColor neutralVariantPaletteKeyColor() const;
  QColor background() const;
  QColor onBackground() const;
  QColor surface() const;
  QColor surfaceDim() const;
  QColor surfaceBright() const;
  QColor surfaceContainerLowest() const;
  QColor surfaceContainerLow() const;
  QColor surfaceContainer() const;
  QColor surfaceContainerHigh() const;
  QColor surfaceContainerHighest() const;
  QColor onSurface() const;
  QColor surfaceVariant() const;
  QColor onSurfaceVariant() const;
  QColor inverseSurface() const;
  QColor inverseOnSurface() const;
  QColor outline() const;
  QColor outlineVariant() const;
  QColor shadow() const;
  QColor scrim() const;
  QColor surfaceTint() const;
  QColor primary() const;
  QColor onPrimary() const;
  QColor primaryContainer() const;
  QColor onPrimaryContainer() const;
  QColor inversePrimary() const;
  QColor secondary() const;
  QColor onSecondary() const;
  QColor secondaryContainer() const;
  QColor onSecondaryContainer() const;
  QColor tertiary() const;
  QColor onTertiary() const;
  QColor tertiaryContainer() const;
  QColor onTertiaryContainer() const;
  QColor error() const;
  QColor onError() const;
  QColor errorContainer() const;
  QColor onErrorContainer() const;
  QColor primaryFixed() const;
  QColor primaryFixedDim() const;
  QColor onPrimaryFixed() const;
  QColor onPrimaryFixedVariant() const;
  QColor secondaryFixed() const;
  QColor secondaryFixedDim() const;
  QColor onSecondaryFixed() const;
  QColor onSecondaryFixedVariant() const;
  QColor tertiaryFixed() const;
  QColor tertiaryFixedDim() const;
  QColor onTertiaryFixed() const;
  QColor onTertiaryFixedVariant() const;

signals:
  void colorSchemeChanged();

private:
  ColorSchemeData m_colorScheme;
};
