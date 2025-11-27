#include "imagetilesnode.h"

ImageNode::ImageNode(QQuickWindow* window, const ImageTiles& imageTiles)
  : m_window(window)
{
  loadImageTiles(imageTiles);
}

void ImageNode::loadImageTiles(const ImageTiles& imageTiles)
{
  if (m_window.isNull())
  {
    qWarning() << "cannot create Image textures without window";
    return;
  }

  m_tiles.clear();

  for (const std::vector<QImage>& row : imageTiles.imageTiles())
  {
    TileRow tileRow;
    tileRow.sourceSize.setHeight(row.front().height());
    tileRow.sourceSize.setWidth(0);

    for (const QImage& tile : row)
    {
      QSGTexture* texture = m_window->createTextureFromImage(tile);
      TileInfo tileInfo;
      tileInfo.texture.reset(texture);
      tileInfo.sourceSize = tile.size();
      tileRow.sourceSize.rwidth() += tile.width();

      tileRow.tiles.emplace_back(std::move(tileInfo));
    }
    m_tiles.push_back(std::move(tileRow));
  }

  m_imageResolution = imageTiles.resolution();
}

void ImageNode::updateGeometry(const QSizeF& contentSize)
{
  qreal x = 0;
  qreal y = 0;
  for (TileRow& row : m_tiles)
  {
    const qreal rowHeight = contentSize.height() * row.sourceSize.height() /
                            m_imageResolution.height();
    row.scaledSize.setHeight(rowHeight);
    row.scaledSize.setWidth(0);
    for (TileInfo& tile : row.tiles)
    {
      const qreal tileWidth = contentSize.height() * tile.sourceSize.width() /
                              m_imageResolution.height();
      row.scaledSize.rwidth() += tileWidth;
      tile.scaledTileRect.setRect(x, y, tileWidth, rowHeight);

      x += tileWidth;
    }

    x = 0;
    y += rowHeight;
  }
}

void ImageNode::updateImageNodes(const QSizeF& itemSize,
                                 const QRectF& contentRect)
{
  if (m_window.isNull())
  {
    qWarning() << "cannot create Image nodes without window";
    return;
  }

  const double xOffset = contentRect.x();
  const double yOffset = contentRect.y();

#ifdef QT_DEBUG
  if (xOffset < 0 || xOffset > contentRect.width())
  {
    qWarning() << "x offset out of bounds" << xOffset;
    return;
  }
  if (yOffset < 0 || yOffset > contentRect.height() - itemSize.height())
  {
    qWarning() << "y offset out of bounds" << yOffset;
    return;
  }
#endif

  removeAllChildNodes();
  for (size_t rowIndex = 0; rowIndex < m_tiles.size(); rowIndex++)
  {
    const int columnCount = m_tiles[rowIndex].tiles.size();
    const double xEndPosition = itemSize.width() + xOffset;

    int columnIndex = 0;
    while (m_tiles[rowIndex].tiles[columnIndex].scaledTileRect.right() <
           xOffset)
    {
      columnIndex = (columnIndex + 1) % columnCount;
    }

    double x =
        m_tiles[rowIndex].tiles[columnIndex].scaledTileRect.x() - xOffset;
    while (x <= xEndPosition)
    {
      const TileInfo& tile = m_tiles[rowIndex].tiles[columnIndex];

      auto imageNode = m_window->createImageNode();
      imageNode->setTexture(tile.texture.get());
      imageNode->setOwnsTexture(false);
      imageNode->setFiltering(QSGTexture::Linear);
      appendChildNode(imageNode);

      imageNode->setRect(x, tile.scaledTileRect.y() - yOffset,
                         tile.scaledTileRect.width(),
                         tile.scaledTileRect.height());

      x += tile.scaledTileRect.width();
      columnIndex = (columnIndex + 1) % columnCount;
    }
  }
}
