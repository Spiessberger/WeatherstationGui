#pragma once

#include <QObject>
#include <QQmlEngine>

#include "colorscheme.h"

class ColorSchemeLoader : public QObject
{
  Q_OBJECT
  QML_ELEMENT

  // clang-format off
  Q_PROPERTY(ColorScheme* colorScheme READ colorScheme WRITE setColorScheme NOTIFY colorSchemeChanged FINAL REQUIRED)
  Q_PROPERTY(ColorSchemeLoader::Theme theme READ theme WRITE setTheme NOTIFY themeChanged FINAL)
  Q_PROPERTY(double contrast READ contrast WRITE setContrast NOTIFY contrastChanged FINAL)
  // clang-format on
public:
  enum Theme
  {
    Light,
    Dark
  };
  Q_ENUM(Theme)

  ColorSchemeLoader() = default;

  Q_INVOKABLE std::vector<QColor> colorsFromImage(const QUrl& imagePath);
  Q_INVOKABLE void loadSchemeFromColor(const QColor& color);

  ColorScheme* colorScheme() const;
  void setColorScheme(ColorScheme* newColorScheme);

  ColorSchemeLoader::Theme theme() const;
  void setTheme(ColorSchemeLoader::Theme newTheme);

  double contrast() const;
  void setContrast(double newContrast);

signals:
  void colorSchemeChanged();
  void themeChanged();
  void contrastChanged();

private:
  void updateColorScheme();

  QPointer<ColorScheme> m_colorScheme = nullptr;
  Theme m_theme = Theme::Light;
  double m_contrast = 0.0;
  QColor m_sourceColor;
};
