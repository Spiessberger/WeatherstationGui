#include "panomaximageprovider.h"

#include <QStringLiteral>

namespace wsgui {
namespace panomax {

const QString PanomaxImageProvider::providerId = QStringLiteral("panomax");

PanomaxImageProvider::PanomaxImageProvider() : QQuickImageProvider{QQuickImageProvider::Image}
{
}

QImage PanomaxImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
  QStringList idParts = id.split('/', Qt::SkipEmptyParts);

  if (idParts.size() != 3)
  {
    qWarning() << "invalid image id" << id;
    return QImage{};
  }

  bool ok = false;
  int tile = idParts[2].toInt(&ok);

  if (!ok || tile < 0 || tile >= m_recentImageTiles.size())
  {
    qWarning() << "invalid tile number" << idParts[2];
    return QImage{};
  }

  if (size)
  {
    *size = m_recentImageTiles[tile].size();
  }

  return m_recentImageTiles[tile];
}

void PanomaxImageProvider::setRecentImageTile(const std::vector<QImage>& imageTiles)
{
  m_recentImageTiles = imageTiles;
}

} // namespace panomax
} // namespace wsgui
