#include "colorschemegenerator.h"

#include <QDebug>

#include <algorithm>
#include <cmath>

#include <material_color_utilities/dynamiccolor/dynamic_scheme.h>
#include <material_color_utilities/quantize/celebi.h>
#include <material_color_utilities/scheme/scheme_tonal_spot.h>
#include <material_color_utilities/score/score.h>

using namespace material_color_utilities;

namespace wsgui::core
{
namespace
{
// the quantizer only needs a coarse color distribution; downscaling
// bounds its runtime independently of the source resolution
constexpr qint64 MaxQuantizerPixels = 128 * 128;
} // namespace

std::vector<QColor> extractColorsFromImage(const QImage& image)
{
  if (image.isNull())
  {
    return {};
  }

  QImage sampled = image;
  const qint64 pixelCount = qint64{image.width()} * image.height();
  if (pixelCount > MaxQuantizerPixels)
  {
    const double scale =
        std::sqrt(static_cast<double>(MaxQuantizerPixels) / pixelCount);
    sampled =
        image.scaled(std::max(1, static_cast<int>(image.width() * scale)),
                     std::max(1, static_cast<int>(image.height() * scale)),
                     Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  }

  // Format_RGB32 stores one QRgb per pixel with alpha forced to 0xff,
  // matching the Argb layout the quantizer expects
  sampled = sampled.convertToFormat(QImage::Format_RGB32);

  std::vector<Argb> pixels;
  pixels.reserve(static_cast<size_t>(sampled.width()) * sampled.height());

  for (int y = 0; y < sampled.height(); y++)
  {
    const QRgb* line = reinterpret_cast<const QRgb*>(sampled.constScanLine(y));
    pixels.insert(pixels.end(), line, line + sampled.width());
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
    return {};
  }

  return extractColorsFromImage(image);
}

ColorSchemeData colorSchemeFromColor(const QColor& color, Theme theme,
                                     double contrastLevel)
{
  const Hct hct{color.rgb()};
  const bool isDark = (theme == Theme::Dark);
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

} // namespace wsgui::core
