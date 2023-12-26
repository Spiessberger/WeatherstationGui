#pragma once

#include <QQmlEngine>
#include <QQuickImageProvider>

#include "panomaximage.h"

namespace wsgui {
namespace panomax {

class PanomaxImageProvider : public QQuickImageProvider
{
  Q_OBJECT
public:
  static const QString providerId;

  PanomaxImageProvider();

  // id: <ISO 8601 Datetime>/<resolution>/<tile>
  QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

private:
  std::vector<PanomaxImage> m_images;
};

} // namespace panomax
} // namespace wsgui
