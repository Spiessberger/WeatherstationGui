#include "colorschemeloader.h"

#include <QQmlFile>

#include <colorschemegenerator.h>

namespace wsgui::quick
{

std::vector<QColor> ColorSchemeLoader::colorsFromImage(const QUrl& imagePath)
{
  return core::extractColorsFromImageFile(
      QQmlFile::urlToLocalFileOrQrc(imagePath));
}

void ColorSchemeLoader::loadSchemeFromColor(const QColor& color)
{
  if (m_sourceColor != color)
  {
    m_sourceColor = color;
    updateColorScheme();
  }
}

ColorScheme* ColorSchemeLoader::colorScheme() const
{
  return m_colorScheme;
}

void ColorSchemeLoader::setColorScheme(ColorScheme* newColorScheme)
{
  if (m_colorScheme == newColorScheme)
  {
    return;
  }
  m_colorScheme = newColorScheme;
  emit colorSchemeChanged();

  updateColorScheme();
}

core::Theme ColorSchemeLoader::theme() const
{
  return m_theme;
}

void ColorSchemeLoader::setTheme(core::Theme newTheme)
{
  if (m_theme == newTheme)
  {
    return;
  }
  m_theme = newTheme;
  emit themeChanged();

  updateColorScheme();
}

double ColorSchemeLoader::contrast() const
{
  return m_contrast;
}

void ColorSchemeLoader::setContrast(double newContrast)
{
  if (qFuzzyCompare(m_contrast, newContrast))
  {
    return;
  }
  m_contrast = newContrast;
  emit contrastChanged();

  updateColorScheme();
}

void ColorSchemeLoader::updateColorScheme()
{
  if (m_colorScheme.isNull())
  {
    return;
  }

  m_colorScheme->setColorScheme(
      core::colorSchemeFromColor(m_sourceColor, m_theme, m_contrast));
}

} // namespace wsgui::quick
