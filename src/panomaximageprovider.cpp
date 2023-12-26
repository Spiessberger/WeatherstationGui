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

  QDateTime imageTime = QDateTime::fromString(idParts[0], Qt::ISODate);
  if (imageTime.isNull() || !imageTime.isValid())
  {
    qWarning() << "invalid image time" << idParts[0];
    return QImage{};
  }

  auto iter = std::find_if(m_images.cbegin(), m_images.cend(), [imageTime](const PanomaxImage& image) {
    return image.imageTime() == imageTime;
  });

  if (iter == m_images.cend())
  {
    qWarning() << "no image with time" << imageTime;
    return QImage{};
  }

  PanomaxImageSize::Resolution resolution = PanomaxImageSize::stringToResolution(idParts[1]);
  if (resolution == PanomaxImageSize::None)
  {
    qWarning() << "invalid image resolution" << idParts[1];
    return QImage{};
  }

  if (!iter->isAvailable(resolution))
  {
    qWarning() << "image with time" << imageTime << "not available in resolution" << idParts[1];
    return QImage{};
  }

  bool ok = false;
  int tile = idParts[2].toInt(&ok);

  if (!ok || tile < 0)
  {
    qWarning() << "invalid tile index" << idParts[2];
    return QImage{};
  }

  QImage image = iter->imageTile(resolution, tile);

  if (!image.isNull() && size != nullptr)
  {
    *size = image.size();
  }

  return image;
}

} // namespace panomax
} // namespace wsgui
