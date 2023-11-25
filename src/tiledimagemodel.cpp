#include "tiledimagemodel.h"

#include <QDateTime>
#include <QImage>

namespace wsgui {

TiledImageModel::TiledImageModel(QObject* parent) : QAbstractListModel(parent)
{
}

QSizeF TiledImageModel::sourceSize() const
{
  return m_sourceSize;
}

void TiledImageModel::setSourceSize(const QSizeF& newSourceSize)
{
  if (m_sourceSize == newSourceSize)
  {
    return;
  }
  m_sourceSize = newSourceSize;
  emit sourceSizeChanged();
}

int TiledImageModel::tileWidth(int index) const
{
  if (index >= 0 && index < m_tiles.size())
  {
    return m_tiles[index].width;
  }
  return 0;
}

int TiledImageModel::tileHeight(int index) const
{
  if (index >= 0 && index < m_tiles.size())
  {
    return m_tiles[index].height;
  }
  return 0;
}

void TiledImageModel::setTiles(const std::vector<ImageTile>& imageTiles)
{
  beginResetModel();
  m_tiles = imageTiles;
  endResetModel();

  int sourceWidth = 0;
  int sourceHeight = 0;
  for (const auto& tile : m_tiles)
  {
    sourceWidth += tile.width;
    sourceHeight = std::max(sourceHeight, tile.height);
  }
  setSourceSize({static_cast<qreal>(sourceWidth), static_cast<qreal>(sourceHeight)});
}

int TiledImageModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }
  return static_cast<int>(m_tiles.size());
}

QVariant TiledImageModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(m_tiles.size()))
  {
    return QVariant();
  }

  switch (role)
  {
  case Roles::Source:
    return m_tiles[index.row()].source;
  case Roles::Width:
    return m_tiles[index.row()].width;
  case Roles::Height:
    return m_tiles[index.row()].height;
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> TiledImageModel::roleNames() const
{
  return {{Roles::Source, "source"}, {Roles::Width, "width"}, {Roles::Height, "height"}};
}

} // namespace wsgui
