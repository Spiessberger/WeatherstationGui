#include <QColor>
#include <QDebug>

#include <material_color_utilities/dynamiccolor/dynamic_scheme.h>
#include <material_color_utilities/scheme/scheme_tonal_spot.h>

using namespace material_color_utilities;

int main(int argc, char* argv[])
{
  QColor sourceColor = Qt::cyan;

  Hct hct{sourceColor.rgb()};
  DynamicScheme scheme = SchemeTonalSpot(hct, false, 0.0);

  qDebug() << "source color:" << sourceColor;
  qDebug() << "primary:" << QColor::fromRgb(scheme.GetPrimary());
  qDebug() << "on primary:" << QColor::fromRgb(scheme.GetOnPrimary());

  return 0;
}
