#include "panoramaview.h"

#include "imagetilesnode.h"

#include <algorithm>

using namespace std::chrono_literals;

QSizeF scaleToHeight(const QSizeF& size, double height)
{
  return size.scaled(1, height, Qt::KeepAspectRatioByExpanding);
}

PanoramaView::PanoramaView() : m_contentRect(0, 0, 0, 0)
{
  setFlags(QQuickItem::ItemHasContents);
  setAcceptTouchEvents(true);
  setAcceptedMouseButtons(Qt::LeftButton);

  // m_autoScrollResumeTimer.setInterval(m_autoScrollResumeDelay);
  // m_autoScrollResumeTimer.setSingleShot(true);

  // m_resetZoomAnimation.setDuration(500);
  // m_resetZoomAnimation.setEasingCurve(QEasingCurve{QEasingCurve::InOutQuad});

  // connect(&m_autoScrollAnimation, &QVariantAnimation::valueChanged, this,
  // &QmlPanoramaView::updateContentXPosition); connect(&m_autoScrollAnimation,
  // &QVariantAnimation::finished, this,
  // &QmlPanoramaView::startAutoScrollAnimation); connect(&m_resetZoomAnimation,
  // &QVariantAnimation::valueChanged, this,
  // &QmlPanoramaView::updateContentRect); connect(&m_resetZoomAnimation,
  // &QVariantAnimation::finished, this,
  // &QmlPanoramaView::startAutoScrollAnimation);
  // connect(&m_autoScrollResumeTimer, &QTimer::timeout, this,
  // &QmlPanoramaView::startAutoScrollAnimation);
}

const ImageTiles& PanoramaView::imageTiles() const
{
  return m_imageTiles;
}

void PanoramaView::setImageTiles(const ImageTiles& imageTiles)
{
  const QSize oldRes = m_imageTiles.resolution();
  const QSize newRes = imageTiles.resolution();

  m_imageTiles = imageTiles;
  emit imageTilesChanged();

  m_imageTilesChanged = true;

  if (oldRes != newRes)
  {
    const QSizeF contentSize = scaleToHeight(newRes, height() * m_zoomFactor);
    if (contentSize != m_contentRect.size())
    {
      setContentRect(m_contentRect.x(), m_contentRect.y(), contentSize.width(),
                     contentSize.height());
    }
  }
  update();
}

bool PanoramaView::autoScroll() const
{
  return m_autoScroll;
}

void PanoramaView::setAutoScroll(bool autoScroll)
{
  if (m_autoScroll == autoScroll)
  {
    return;
  }

  m_autoScroll = autoScroll;
  emit autoScrollChanged();
}

void PanoramaView::componentComplete()
{
  QQuickItem::componentComplete();
}

QSGNode* PanoramaView::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
  if (size().isEmpty() || m_imageTiles.resolution().isEmpty() ||
      m_contentRect.isEmpty())
  {
    if (oldNode)
    {
      delete oldNode;
    }
    return nullptr;
  }

  auto node = static_cast<ImageNode*>(oldNode);

  if (node == nullptr || m_imageTilesChanged)
  {
    if (node)
    {
      delete node;
    }
    node = new ImageNode(window(), m_imageTiles);
    m_contentSizeChanged = true;
    m_contentPositionChanged = true;
  }

  if (m_contentSizeChanged)
  {
    node->updateGeometry(m_contentRect.size());
    m_contentPositionChanged = true;
  }

  if (m_contentPositionChanged)
  {
    node->updateImageNodes(size(), m_contentRect);
  }

  m_contentSizeChanged = false;
  m_imageTilesChanged = false;
  m_contentPositionChanged = false;

  return node;
}

void PanoramaView::geometryChange(const QRectF& newGeometry,
                                  const QRectF& oldGeometry)
{
  QQuickItem::geometryChange(newGeometry, oldGeometry);

  if (m_imageTiles.isNull())
  {
    return;
  }

  const QSizeF scaledImageSize =
      scaleToHeight(m_imageTiles.resolution().toSizeF(), newGeometry.height());

  QPointF contentCenter;
  contentCenter.setX(oldGeometry.width() / 2);
  contentCenter.setY(oldGeometry.height() / 2);
  if (m_contentRect.x() > 0)
  {
    contentCenter.rx() += m_contentRect.x();
  }
  if (m_contentRect.y() > 0)
  {
    contentCenter.ry() += m_contentRect.y();
  }

  QPointF itemCenter;
  itemCenter.setX(newGeometry.width() / 2);
  itemCenter.setY(newGeometry.height() / 2);

  updateContentSize(scaledImageSize, contentCenter, itemCenter);
}

void PanoramaView::touchEvent(QTouchEvent* event)
{
  if (event->pointCount() == 0)
  {
    return;
  }

  const auto& points = event->points();
  QPointF sum = std::accumulate(points.cbegin(), points.cend(), QPointF(0, 0),
                                [](const QPointF& acc, const QEventPoint& point)
                                { return acc + point.position(); });
  QPointF center = sum / event->pointCount();

  const bool isDragStart =
      std::ranges::any_of(points, [](const QEventPoint& point)
                          { return point.state() == QEventPoint::Pressed; });

  if (isDragStart)
  {
    m_dragStartPosition = center;
    m_dragInitialContentPosition = m_contentRect.topLeft();
  }
  else
  {
    const double xDiff = m_dragStartPosition.x() - center.x();
    const double yDiff = m_dragStartPosition.y() - center.y();
    setContentPosition(m_dragInitialContentPosition.x() + xDiff,
                       m_dragInitialContentPosition.y() + yDiff);
  }
}

void PanoramaView::mousePressEvent(QMouseEvent* event)
{
  m_dragStartPosition = event->position();
  m_dragInitialContentPosition = m_contentRect.topLeft();
}

void PanoramaView::mouseMoveEvent(QMouseEvent* event)
{
  const double xDiff = m_dragStartPosition.x() - event->position().x();
  const double yDiff = m_dragStartPosition.y() - event->position().y();
  setContentPosition(m_dragInitialContentPosition.x() + xDiff,
                     m_dragInitialContentPosition.y() + yDiff);
}

void PanoramaView::mouseReleaseEvent(QMouseEvent* event)
{
  Q_UNUSED(event)
}

void PanoramaView::wheelEvent(QWheelEvent* event)
{
  const double zoomLevel =
      std::clamp<double>(m_zoomLevel + event->angleDelta().y() / 1000.0, 1, 10);

  if (qFuzzyCompare(zoomLevel, m_zoomLevel))
  {
    return;
  }

  m_zoomLevel = zoomLevel;
  m_zoomFactor = std::pow(2, m_zoomLevel - 1);

  const QSizeF scaledImageSize = scaleToHeight(
      m_imageTiles.resolution().toSizeF(), height() * m_zoomFactor);

  updateContentSize(scaledImageSize,
                    event->position() + m_contentRect.topLeft(),
                    event->position());
}

void PanoramaView::updateContentSize(const QSizeF& newSize,
                                     const QPointF& contentAnchorPoint,
                                     const QPointF& itemAnchorPoint)
{
  if (m_contentRect.isEmpty())
  {
    setContentRect(0, 0, newSize.width(), newSize.height());
    return;
  }

  const double relativeXCenter = contentAnchorPoint.x() / m_contentRect.width();
  const double relativeYCenter =
      contentAnchorPoint.y() / m_contentRect.height();
  const double newXCenter = relativeXCenter * newSize.width();
  const double newYCenter = relativeYCenter * newSize.height();

  QRectF contentRect;
  contentRect.setX(newXCenter - itemAnchorPoint.x());
  contentRect.setY(newYCenter - itemAnchorPoint.y());
  contentRect.setSize(newSize);

  setContentRect(contentRect);
}

void PanoramaView::setContentRect(const QRectF& contentRect)
{
  setContentRect(contentRect.x(), contentRect.y(), contentRect.width(),
                 contentRect.height());
}

void PanoramaView::setContentRect(double xPosition, double yPosition,
                                  double width, double height)
{
  const QRectF contentRect =
      sanitizedContentRect(xPosition, yPosition, width, height);

  if (contentRect.size() != m_contentRect.size())
  {
    m_contentSizeChanged = true;
  }
  if (contentRect.topLeft() != m_contentRect.topLeft())
  {
    m_contentPositionChanged = true;
  }

  if (m_contentPositionChanged || m_contentSizeChanged)
  {
    m_contentRect = contentRect;
    update();
  }
}

QRectF PanoramaView::sanitizedContentRect(double xPosition, double yPosition,
                                          double width, double height)
{
  const QSizeF itemSize = size();

  width = std::max<double>(0, width);
  height = std::max<double>(0, height);

  if (qFuzzyIsNull(width) || qFuzzyIsNull(height))
  {
    return {0, 0, 0, 0};
  }

  // wrap x position
  xPosition = std::fmod(xPosition, width);
  if (xPosition < 0)
  {
    xPosition += width;
  }

  // clamp y position
  if (height > itemSize.height())
  {
    yPosition = std::clamp<double>(yPosition, 0, height - itemSize.height());
  }
  else
  {
    yPosition = 0;
  }

  return {xPosition, yPosition, width, height};
}

void PanoramaView::setContentPosition(double xPosition, double yPosition)
{
  setContentRect(xPosition, yPosition, m_contentRect.width(),
                 m_contentRect.height());
}

// void QmlPanoramaView::startAutoScrollAnimation()
// {
//   if (m_contentRect.isEmpty())
//   {
//     return;
//   }

//   const bool resetZoom = !qFuzzyCompare(m_contentRect.height(), height());
//   if (resetZoom)
//   {
//     m_zoomFactor = 1.0;

//     QRectF targetRect;
//     targetRect.setSize(m_imageTiles.resolution().toSizeF().scaled(1,
//     height(), Qt::KeepAspectRatioByExpanding));

//     double xCenter = width() / 2 + m_contentRect.x();
//     double relativeXCenter = xCenter / m_contentRect.width();
//     targetRect.moveLeft(relativeXCenter * targetRect.width() - width() / 2);

//     m_resetZoomAnimation.setStartValue(m_contentRect);
//     m_resetZoomAnimation.setEndValue(targetRect);
//     m_resetZoomAnimation.start();

//     return;
//   }

//   double startXPos = m_contentRect.x();
//   double targetXPos = m_contentRect.width();

//   std::chrono::milliseconds scrollDuration = m_autoScrollDuration;

//   if (startXPos > 0 && startXPos < m_contentRect.width())
//   {
//     scrollDuration =
//       std::chrono::duration_cast<std::chrono::milliseconds>(scrollDuration *
//       (1 - startXPos / targetXPos));
//   }
//   else
//   {
//     startXPos = 0;
//   }

//   m_autoScrollAnimation.setStartValue(startXPos);
//   m_autoScrollAnimation.setEndValue(targetXPos);
//   m_autoScrollAnimation.setDuration(scrollDuration.count());
//   m_autoScrollAnimation.start();
// }

// void QmlPanoramaView::updateContentXPosition(const QVariant& xPosition)
// {
//   setContentPosition(xPosition.toDouble(), 0);
// }

// void QmlPanoramaView::updateContentRect(const QVariant& rect)
// {
//   setContentRect(m_resetZoomAnimation.currentValue().toRectF());
// }
