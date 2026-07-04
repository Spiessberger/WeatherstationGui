#pragma once

#include <QColor>
#include <QImage>
#include <QString>

#include "colorschemedata.h"
#include "wsguienums.h"

namespace wsgui::core
{

std::vector<QColor> extractColorsFromImage(const QImage& image);
std::vector<QColor> extractColorsFromImageFile(const QString& imagePath);

ColorSchemeData colorSchemeFromColor(const QColor& color, Theme theme,
                                     double contrastLevel = 0.0);

} // namespace wsgui::core
