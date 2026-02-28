#pragma once

#include <QColor>
#include <QImage>
#include <QString>

#include "colorschemedata.h"

enum class ColorSchemeTheme
{
  Light,
  Dark
};

std::vector<QColor> extractColorsFromImage(const QImage& image);
std::vector<QColor> extractColorsFromImageFile(const QString& imagePath);

ColorSchemeData colorSchemeFromColor(const QColor& color,
                                     ColorSchemeTheme theme,
                                     double contrastLevel = 0.0);
