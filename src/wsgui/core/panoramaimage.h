#pragma once

#include <QImage>
#include <QQuickItem>

namespace wsgui
{
namespace core
{

class PanoramaImage : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(std::vector<QImage> images READ images WRITE setImages NOTIFY imagesChanged FINAL)
  Q_PROPERTY(qreal xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged FINAL)
  Q_PROPERTY(QSizeF sourceSize READ sourceSize WRITE setSourceSize NOTIFY sourceSizeChanged FINAL)

  QML_ELEMENT
public:
  PanoramaImage(QQuickItem* parent = nullptr);

  const std::vector<QImage>& images() const;
  void setImages(const std::vector<QImage>& newImages);

  qreal xOffset() const;
  void setXOffset(qreal newXOffset);

  QSizeF sourceSize() const;

signals:
  void imagesChanged();
  void sourceSizeChanged();

  void xOffsetChanged();

protected:
  void componentComplete() override;
  QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;
  void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;

  void setSourceSize(const QSizeF& newSourceSize);

private:
  std::vector<QImage> m_images;
  QSizeF m_sourceSize;
  qreal m_xOffset = 0;
  bool m_updateImageNode = false;
  bool m_updateImageNodeScaling = false;
};

} // namespace core
} // namespace wsgui
