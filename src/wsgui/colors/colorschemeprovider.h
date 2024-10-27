#pragma once

#include <QImage>
#include <QObject>
#include <QQmlEngine>

#include "colorscheme.h"

namespace wsgui
{
namespace colors
{

class ColorSchemeProvider : public QObject
{
  Q_OBJECT
  Q_PROPERTY(std::vector<QColor> seedColors READ seedColors NOTIFY seedColorsChanged FINAL)
  Q_PROPERTY(wsgui::colors::ColorScheme* colorScheme READ colorScheme CONSTANT FINAL)
  Q_PROPERTY(bool isDark READ isDark WRITE setIsDark NOTIFY isDarkChanged FINAL)
  Q_PROPERTY(double contrast READ contrast WRITE setContrast NOTIFY contrastChanged FINAL)
  Q_PROPERTY(int preferedSeedColorIndex READ preferedSeedColorIndex WRITE setPreferedSeedColorIndex
                 NOTIFY preferedSeedColorIndexChanged FINAL)
  QML_ELEMENT
public:
  ColorSchemeProvider() = default;

  Q_INVOKABLE void loadSeedColorsFromImage(const QImage& image);
  Q_INVOKABLE void loadSchemeFromColor(const QColor& seedColor);

  const std::vector<QColor>& seedColors() const;

  bool isDark() const;
  void setIsDark(bool newIsDark);

  double contrast() const;
  void setContrast(double newContrast);

  int preferedSeedColorIndex() const;
  void setPreferedSeedColorIndex(int newPreferedSeedColorIndex);

signals:
  void seedColorsChanged();
  void colorsChanged();
  void isDarkChanged();
  void contrastChanged();
  void preferedSeedColorIndexChanged();

private:
  ColorScheme* colorScheme();
  void reloadColorSchemeFromSeedColors();

  std::vector<QColor> m_seedColors;
  ColorScheme m_colorScheme;
  bool m_isDark = false;
  double m_contrast = 0.0;
  int m_preferedSeedColorIndex = 0;
};

} // namespace colors
} // namespace wsgui
