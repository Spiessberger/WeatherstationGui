#include <QColor>
#include <QDebug>
#include <QFile>
#include <QImage>

#include <material_color_utilities/quantize/celebi.h>
#include <material_color_utilities/score/score.h>

using namespace material_color_utilities;

int main(int argc, char* argv[])
{
  QImage image{":/21-00-00_thumb.jpg"};

  if (image.isNull())
  {
    qWarning() << "failed to load image";
    return 1;
  }

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

  std::vector<Argb> colors = RankedSuggestions(quantizerResult.color_to_count);

  for (Argb color : colors)
  {
    qDebug() << QColor::fromRgb(color);
  }

  return 0;
}
