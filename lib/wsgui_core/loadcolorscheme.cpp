#include "loadcolorscheme.h"

#include <QDebug>

#include <algorithm>

#include <material_color_utilities/dynamiccolor/dynamic_scheme.h>
#include <material_color_utilities/quantize/celebi.h>
#include <material_color_utilities/scheme/scheme_tonal_spot.h>
#include <material_color_utilities/score/score.h>

using namespace material_color_utilities;

std::vector<QColor> extractColorsFromImage(const QImage& image)
{
  std::vector<Argb> pixels;
  pixels.reserve(image.width() * image.height());

  for (int y = 0; y < image.height(); y++)
  {
    for (int x = 0; x < image.width(); x++)
    {
      pixels.push_back(image.pixelColor(x, y).rgb());
    }
  }

  QuantizerResult quantizerResult = QuantizeCelebi(pixels, 128);

  std::vector<QColor> colors;
  std::ranges::transform(RankedSuggestions(quantizerResult.color_to_count),
                         std::back_inserter(colors),
                         [](Argb color) { return QColor::fromRgb(color); });

  return colors;
}

std::vector<QColor> extractColorsFromImageFile(const QString& imagePath)
{
  QImage image{imagePath};

  if (image.isNull())
  {
    qWarning() << "failed to load image from" << imagePath;
  }

  return extractColorsFromImage(image);
}

ColorSchemeData colorSchemeFromColor(const QColor& color,
                                     ColorSchemeTheme theme,
                                     double contrastLevel)
{
  const Hct hct{color.rgb()};
  const bool isDark = (theme == ColorSchemeTheme::Dark);
  const DynamicScheme scheme = SchemeTonalSpot(hct, isDark, contrastLevel);

  ColorSchemeData data;

  // clang-format off
  data.primaryPaletteKeyColor = QColor::fromRgb(scheme.GetPrimaryPaletteKeyColor());
  data.secondaryPaletteKeyColor = QColor::fromRgb(scheme.GetSecondaryPaletteKeyColor());
  data.tertiaryPaletteKeyColor = QColor::fromRgb(scheme.GetTertiaryPaletteKeyColor());
  data.neutralPaletteKeyColor = QColor::fromRgb(scheme.GetNeutralPaletteKeyColor());
  data.neutralVariantPaletteKeyColor = QColor::fromRgb(scheme.GetNeutralVariantPaletteKeyColor());  
  data.background = QColor::fromRgb(scheme.GetBackground());
  data.onBackground = QColor::fromRgb(scheme.GetOnBackground());
  data.surface = QColor::fromRgb(scheme.GetSurface());
  data.surfaceDim = QColor::fromRgb(scheme.GetSurfaceDim());
  data.surfaceBright = QColor::fromRgb(scheme.GetSurfaceBright());
  data.surfaceContainerLowest = QColor::fromRgb(scheme.GetSurfaceContainerLowest());
  data.surfaceContainerLow = QColor::fromRgb(scheme.GetSurfaceContainerLow());
  data.surfaceContainer = QColor::fromRgb(scheme.GetSurfaceContainer());
  data.surfaceContainerHigh = QColor::fromRgb(scheme.GetSurfaceContainerHigh());
  data.surfaceContainerHighest = QColor::fromRgb(scheme.GetSurfaceContainerHighest());
  data.onSurface = QColor::fromRgb(scheme.GetOnSurface());
  data.surfaceVariant = QColor::fromRgb(scheme.GetSurfaceVariant());
  data.onSurfaceVariant = QColor::fromRgb(scheme.GetOnSurfaceVariant());
  data.inverseSurface = QColor::fromRgb(scheme.GetInverseSurface());
  data.inverseOnSurface = QColor::fromRgb(scheme.GetInverseOnSurface());
  data.outline = QColor::fromRgb(scheme.GetOutline());
  data.outlineVariant = QColor::fromRgb(scheme.GetOutlineVariant());
  data.shadow = QColor::fromRgb(scheme.GetShadow());
  data.scrim = QColor::fromRgb(scheme.GetScrim());
  data.surfaceTint = QColor::fromRgb(scheme.GetSurfaceTint());  
  data.primary = QColor::fromRgb(scheme.GetPrimary());
  data.onPrimary = QColor::fromRgb(scheme.GetOnPrimary());
  data.primaryContainer = QColor::fromRgb(scheme.GetPrimaryContainer());
  data.onPrimaryContainer = QColor::fromRgb(scheme.GetOnPrimaryContainer());
  data.inversePrimary = QColor::fromRgb(scheme.GetInversePrimary());  
  data.secondary = QColor::fromRgb(scheme.GetSecondary());
  data.onSecondary = QColor::fromRgb(scheme.GetOnSecondary());
  data.secondaryContainer = QColor::fromRgb(scheme.GetSecondaryContainer());
  data.onSecondaryContainer = QColor::fromRgb(scheme.GetOnSecondaryContainer());  
  data.tertiary = QColor::fromRgb(scheme.GetTertiary());
  data.onTertiary = QColor::fromRgb(scheme.GetOnTertiary());
  data.tertiaryContainer = QColor::fromRgb(scheme.GetTertiaryContainer());
  data.onTertiaryContainer = QColor::fromRgb(scheme.GetOnTertiaryContainer());  
  data.error = QColor::fromRgb(scheme.GetError());
  data.onError = QColor::fromRgb(scheme.GetOnError());
  data.errorContainer = QColor::fromRgb(scheme.GetErrorContainer());
  data.onErrorContainer = QColor::fromRgb(scheme.GetOnErrorContainer());  
  data.primaryFixed = QColor::fromRgb(scheme.GetPrimaryFixed());
  data.primaryFixedDim = QColor::fromRgb(scheme.GetPrimaryFixedDim());
  data.onPrimaryFixed = QColor::fromRgb(scheme.GetOnPrimaryFixed());
  data.onPrimaryFixedVariant = QColor::fromRgb(scheme.GetOnPrimaryFixedVariant());  
  data.secondaryFixed = QColor::fromRgb(scheme.GetSecondaryFixed());
  data.secondaryFixedDim = QColor::fromRgb(scheme.GetSecondaryFixedDim());
  data.onSecondaryFixed = QColor::fromRgb(scheme.GetOnSecondaryFixed());
  data.onSecondaryFixedVariant = QColor::fromRgb(scheme.GetOnSecondaryFixedVariant());  
  data.tertiaryFixed = QColor::fromRgb(scheme.GetTertiaryFixed());
  data.tertiaryFixedDim = QColor::fromRgb(scheme.GetTertiaryFixedDim());
  data.onTertiaryFixed = QColor::fromRgb(scheme.GetOnTertiaryFixed());
  data.onTertiaryFixedVariant = QColor::fromRgb(scheme.GetOnTertiaryFixedVariant());
  // clang-format on

  return data;
}
