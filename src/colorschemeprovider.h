#pragma once

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
  QML_ELEMENT
public:
  explicit ColorSchemeProvider(QObject* parent = nullptr);

  Q_INVOKABLE void loadSeedColorsFromImage(const QImage& image);
  Q_INVOKABLE void loadSchemeFromColor(const QColor& seedColor, bool isDark, double contrastLevel);

  const std::vector<QColor>& seedColors() const;

signals:
  void seedColorsChanged();
  void colorsChanged();

private:
  ColorScheme* colorScheme();

  std::vector<QColor> m_seedColors;
  ColorScheme m_colorScheme;
};

} // namespace colors
} // namespace wsgui
