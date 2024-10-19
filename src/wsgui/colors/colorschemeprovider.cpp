#include "colorschemeprovider.h"

#include <material_color_utilities/dynamiccolor/material_dynamic_colors.h>
#include <material_color_utilities/quantize/celebi.h>
#include <material_color_utilities/scheme/scheme_tonal_spot.h>
#include <material_color_utilities/score/score.h>

#include "colorschemedata.h"

namespace wsgui
{
namespace colors
{

ColorSchemeProvider::ColorSchemeProvider(QObject* parent)
    : QObject{parent}
{
}

void ColorSchemeProvider::loadSeedColorsFromImage(const QImage& image)
{
  std::vector<material_color_utilities::Argb> pixels;
  pixels.reserve(image.width() * image.height());

  for (int y = 0; y < image.height(); y++)
  {
    for (int x = 0; x < image.width(); x++)
    {
      pixels.push_back(image.pixel(x, y));
    }
  }

  const auto result = material_color_utilities::QuantizeCelebi(pixels, 128);
  const std::vector<material_color_utilities::Argb> colors =
      material_color_utilities::RankedSuggestions(result.color_to_count);

  m_seedColors.clear();
  m_seedColors.reserve(colors.size());

  for (const material_color_utilities::Argb color: colors)
  {
    // QRgb is stored in format argb
    m_seedColors.push_back(QColor::fromRgb(color));
  }

  emit seedColorsChanged();

  reloadColorSchemeFromSeedColors();
}

void ColorSchemeProvider::loadSchemeFromColor(const QColor& seedColor)
{
  const material_color_utilities::Hct hctColor{seedColor.rgb()};
  const material_color_utilities::DynamicScheme dynamicScheme =
      material_color_utilities::SchemeTonalSpot{hctColor, m_isDark, m_contrast};

  ColorSchemeData scheme;

  using material_color_utilities::MaterialDynamicColors;

  // clang-format off
  scheme.primaryPaletteKeyColor = QColor::fromRgb(MaterialDynamicColors::PrimaryPaletteKeyColor().GetArgb(dynamicScheme));
  scheme.secondaryPaletteKeyColor = QColor::fromRgb(MaterialDynamicColors::SecondaryPaletteKeyColor().GetArgb(dynamicScheme));
  scheme.tertiaryPaletteKeyColor = QColor::fromRgb(MaterialDynamicColors::TertiaryPaletteKeyColor().GetArgb(dynamicScheme));
  scheme.neutralPaletteKeyColor = QColor::fromRgb(MaterialDynamicColors::NeutralPaletteKeyColor().GetArgb(dynamicScheme));
  scheme.neutralVariantPaletteKeyColor = QColor::fromRgb(MaterialDynamicColors::NeutralVariantPaletteKeyColor().GetArgb(dynamicScheme));
  scheme.background = QColor::fromRgb(MaterialDynamicColors::Background().GetArgb(dynamicScheme));
  scheme.onBackground = QColor::fromRgb(MaterialDynamicColors::OnBackground().GetArgb(dynamicScheme));
  scheme.surface = QColor::fromRgb(MaterialDynamicColors::Surface().GetArgb(dynamicScheme));
  scheme.surfaceDim = QColor::fromRgb(MaterialDynamicColors::SurfaceDim().GetArgb(dynamicScheme));
  scheme.surfaceBright = QColor::fromRgb(MaterialDynamicColors::SurfaceBright().GetArgb(dynamicScheme));
  scheme.surfaceContainerLowest = QColor::fromRgb(MaterialDynamicColors::SurfaceContainerLowest().GetArgb(dynamicScheme));
  scheme.surfaceContainerLow = QColor::fromRgb(MaterialDynamicColors::SurfaceContainerLow().GetArgb(dynamicScheme));
  scheme.surfaceContainer = QColor::fromRgb(MaterialDynamicColors::SurfaceContainer().GetArgb(dynamicScheme));
  scheme.surfaceContainerHigh = QColor::fromRgb(MaterialDynamicColors::SurfaceContainerHigh().GetArgb(dynamicScheme));
  scheme.surfaceContainerHighest = QColor::fromRgb(MaterialDynamicColors::SurfaceContainerHighest().GetArgb(dynamicScheme));
  scheme.onSurface = QColor::fromRgb(MaterialDynamicColors::OnSurface().GetArgb(dynamicScheme));
  scheme.surfaceVariant = QColor::fromRgb(MaterialDynamicColors::SurfaceVariant().GetArgb(dynamicScheme));
  scheme.onSurfaceVariant = QColor::fromRgb(MaterialDynamicColors::OnSurfaceVariant().GetArgb(dynamicScheme));
  scheme.inverseSurface = QColor::fromRgb(MaterialDynamicColors::InverseSurface().GetArgb(dynamicScheme));
  scheme.inverseOnSurface = QColor::fromRgb(MaterialDynamicColors::InverseOnSurface().GetArgb(dynamicScheme));
  scheme.outline = QColor::fromRgb(MaterialDynamicColors::Outline().GetArgb(dynamicScheme));
  scheme.outlineVariant = QColor::fromRgb(MaterialDynamicColors::OutlineVariant().GetArgb(dynamicScheme));
  scheme.shadow = QColor::fromRgb(MaterialDynamicColors::Shadow().GetArgb(dynamicScheme));
  scheme.scrim = QColor::fromRgb(MaterialDynamicColors::Scrim().GetArgb(dynamicScheme));
  scheme.surfaceTint = QColor::fromRgb(MaterialDynamicColors::SurfaceTint().GetArgb(dynamicScheme));
  scheme.primary = QColor::fromRgb(MaterialDynamicColors::Primary().GetArgb(dynamicScheme));
  scheme.onPrimary = QColor::fromRgb(MaterialDynamicColors::OnPrimary().GetArgb(dynamicScheme));
  scheme.primaryContainer = QColor::fromRgb(MaterialDynamicColors::PrimaryContainer().GetArgb(dynamicScheme));
  scheme.onPrimaryContainer = QColor::fromRgb(MaterialDynamicColors::OnPrimaryContainer().GetArgb(dynamicScheme));
  scheme.inversePrimary = QColor::fromRgb(MaterialDynamicColors::InversePrimary().GetArgb(dynamicScheme));
  scheme.secondary = QColor::fromRgb(MaterialDynamicColors::Secondary().GetArgb(dynamicScheme));
  scheme.onSecondary = QColor::fromRgb(MaterialDynamicColors::OnSecondary().GetArgb(dynamicScheme));
  scheme.secondaryContainer = QColor::fromRgb(MaterialDynamicColors::SecondaryContainer().GetArgb(dynamicScheme));
  scheme.onSecondaryContainer = QColor::fromRgb(MaterialDynamicColors::OnSecondaryContainer().GetArgb(dynamicScheme));
  scheme.tertiary = QColor::fromRgb(MaterialDynamicColors::Tertiary().GetArgb(dynamicScheme));
  scheme.onTertiary = QColor::fromRgb(MaterialDynamicColors::OnTertiary().GetArgb(dynamicScheme));
  scheme.tertiaryContainer = QColor::fromRgb(MaterialDynamicColors::TertiaryContainer().GetArgb(dynamicScheme));
  scheme.onTertiaryContainer = QColor::fromRgb(MaterialDynamicColors::OnTertiaryContainer().GetArgb(dynamicScheme));
  scheme.error = QColor::fromRgb(MaterialDynamicColors::Error().GetArgb(dynamicScheme));
  scheme.onError = QColor::fromRgb(MaterialDynamicColors::OnError().GetArgb(dynamicScheme));
  scheme.errorContainer = QColor::fromRgb(MaterialDynamicColors::ErrorContainer().GetArgb(dynamicScheme));
  scheme.onErrorContainer = QColor::fromRgb(MaterialDynamicColors::OnErrorContainer().GetArgb(dynamicScheme));
  scheme.primaryFixed = QColor::fromRgb(MaterialDynamicColors::PrimaryFixed().GetArgb(dynamicScheme));
  scheme.primaryFixedDim = QColor::fromRgb(MaterialDynamicColors::PrimaryFixedDim().GetArgb(dynamicScheme));
  scheme.onPrimaryFixed = QColor::fromRgb(MaterialDynamicColors::OnPrimaryFixed().GetArgb(dynamicScheme));
  scheme.onPrimaryFixedVariant = QColor::fromRgb(MaterialDynamicColors::OnPrimaryFixedVariant().GetArgb(dynamicScheme));
  scheme.secondaryFixed = QColor::fromRgb(MaterialDynamicColors::SecondaryFixed().GetArgb(dynamicScheme));
  scheme.secondaryFixedDim = QColor::fromRgb(MaterialDynamicColors::SecondaryFixedDim().GetArgb(dynamicScheme));
  scheme.onSecondaryFixed = QColor::fromRgb(MaterialDynamicColors::OnSecondaryFixed().GetArgb(dynamicScheme));
  scheme.onSecondaryFixedVariant = QColor::fromRgb(MaterialDynamicColors::OnSecondaryFixedVariant().GetArgb(dynamicScheme));
  scheme.tertiaryFixed = QColor::fromRgb(MaterialDynamicColors::TertiaryFixed().GetArgb(dynamicScheme));
  scheme.tertiaryFixedDim = QColor::fromRgb(MaterialDynamicColors::TertiaryFixedDim().GetArgb(dynamicScheme));
  scheme.onTertiaryFixed = QColor::fromRgb(MaterialDynamicColors::OnTertiaryFixed().GetArgb(dynamicScheme));
  scheme.onTertiaryFixedVariant = QColor::fromRgb(MaterialDynamicColors::OnTertiaryFixedVariant().GetArgb(dynamicScheme));
  // clang-format on

  m_colorScheme.setColors(scheme);
  emit colorsChanged();
}

const std::vector<QColor>& ColorSchemeProvider::seedColors() const
{
  return m_seedColors;
}

ColorScheme* ColorSchemeProvider::colorScheme()
{
  QQmlEngine::setObjectOwnership(&m_colorScheme, QQmlEngine::CppOwnership);
  return &m_colorScheme;
}

void ColorSchemeProvider::reloadColorSchemeFromSeedColors()
{
  if (!m_seedColors.empty() && m_preferedSeedColorIndex >= 0
      && m_preferedSeedColorIndex < static_cast<int>(m_seedColors.size()))
  {
    loadSchemeFromColor(m_seedColors[m_preferedSeedColorIndex]);
  }
}

bool ColorSchemeProvider::isDark() const
{
  return m_isDark;
}

void ColorSchemeProvider::setIsDark(bool newIsDark)
{
  if (m_isDark == newIsDark)
  {
    return;
  }
  m_isDark = newIsDark;
  emit isDarkChanged();

  reloadColorSchemeFromSeedColors();
}

double ColorSchemeProvider::contrast() const
{
  return m_contrast;
}

void ColorSchemeProvider::setContrast(double newContrast)
{
  if (qFuzzyCompare(m_contrast, newContrast))
  {
    return;
  }
  m_contrast = newContrast;
  emit contrastChanged();

  reloadColorSchemeFromSeedColors();
}

int ColorSchemeProvider::preferedSeedColorIndex() const
{
  return m_preferedSeedColorIndex;
}

void ColorSchemeProvider::setPreferedSeedColorIndex(int newPreferedSeedColorIndex)
{
  if (m_preferedSeedColorIndex == newPreferedSeedColorIndex)
  {
    return;
  }
  m_preferedSeedColorIndex = newPreferedSeedColorIndex;
  emit preferedSeedColorIndexChanged();

  reloadColorSchemeFromSeedColors();
}

} // namespace colors
} // namespace wsgui
