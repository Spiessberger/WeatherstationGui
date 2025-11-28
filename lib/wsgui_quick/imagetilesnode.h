#pragma once

#include "imagetiles.h"

#include <QSGImageNode>
#include <QSGNode>

class ImageNode : public QSGNode
{
public:
  ImageNode(QQuickWindow* window, const ImageTiles& imageTiles);

  void loadImageTiles(const ImageTiles& imageTiles);

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

  struct ImageNodeInfo
  {
    int columnIndex = 0;
    QSGImageNode* imageNode = nullptr;
  };

  std::vector<TileRow> m_tiles;
  std::vector<std::vector<ImageNodeInfo>> m_imageNodes;
};
