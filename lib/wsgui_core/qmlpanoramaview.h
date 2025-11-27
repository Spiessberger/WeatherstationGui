#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QVariantAnimation>

#include "imagetiles.h"

class QmlPanoramaView : public QQuickItem
{
  Q_OBJECT
  QML_NAMED_ELEMENT(PanoramaView)

  Q_PROPERTY(ImageTiles imageTiles READ imageTiles WRITE setImageTiles NOTIFY imageTilesChanged FINAL)
  Q_PROPERTY(bool autoScroll READ autoScroll WRITE setAutoScroll NOTIFY autoScrollChanged FINAL)
public:
  QmlPanoramaView();

  const ImageTiles& imageTiles() const;
  void setImageTiles(const ImageTiles& imageTiles);

  bool autoScroll() const;
  void setAutoScroll(bool autoScroll);

signals:
  void imageTilesChanged();
  void autoScrollChanged();

protected:
  void componentComplete() override;
  QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;
  void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void touchEvent(QTouchEvent* event) override;

private:
  void updateContentSize(const QSizeF& newSize, const QPointF& contentAnchorPoint, const QPointF& itemAnchorPoint);
  void setContentRect(const QRectF& contentRect);
  void setContentRect(double xPosition, double yPosition, double width, double height);
  QRectF sanitizedContentRect(double xPosition, double yPosition, double width, double height);
  void setContentPosition(double xPosition, double yPosition);
  void startAutoScrollAnimation();
  void updateContentXPosition(const QVariant& xPosition);
  void updateContentRect(const QVariant& rect);

  ImageTiles m_imageTiles;
  bool m_imageTilesChanged = false;
  bool m_contentSizeChanged = false;
  bool m_contentPositionChanged = false;

  std::chrono::seconds m_autoScrollDuration{10};
  std::chrono::seconds m_autoScrollResumeDelay{2};
  bool m_autoScroll = false;

  double m_zoomLevel = 1.0;
  double m_zoomFactor = 1.0;

  // width and height describe the rendered size of the image tiles
  // x and y describe the offset within the item
  QRectF m_contentRect;
  QPointF m_dragStartPosition;
  QPointF m_dragInitialContentPosition;
  // QTimer m_autoScrollResumeTimer;
  // QVariantAnimation m_autoScrollAnimation;
  // QVariantAnimation m_resetZoomAnimation;
};
