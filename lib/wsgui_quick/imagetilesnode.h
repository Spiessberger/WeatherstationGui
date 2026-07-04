#pragma once

#include <imagetiles.h>

#include <QSGImageNode>
#include <QSGNode>

namespace wsgui::quick
{

class ImageTilesNode : public QSGNode
{
public:
  ImageTilesNode(QQuickWindow* window, const core::ImageTiles& imageTiles);

  void loadImageTiles(const core::ImageTiles& imageTiles);

  void updateGeometry(const QSizeF& contentSize);

  // x and y must not be less than 0
  // x must not be greater than contentRect.width
  // y must not be greater that contentRect.height - itemSize.height
  void updateImageNodes(const QSizeF& itemSize, const QRectF& contentRect);

private:
  QPointer<QQuickWindow> m_window;
  QSize m_imageResolution;

  struct TileInfo
  {
    QSize sourceSize;
    QRectF scaledTileRect;
    std::unique_ptr<QSGTexture> texture;
  };

  struct TileRow
  {
    QSize sourceSize;
    QSizeF scaledSize;
    std::vector<TileInfo> tiles;
  };

  std::vector<TileRow> m_tiles;
};

} // namespace wsgui::quick
