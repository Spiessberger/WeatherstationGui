#include "imagewrapproxymodel.h"

namespace wsgui {

ImageWrapProxyModel::ImageWrapProxyModel()
{
}

QModelIndex ImageWrapProxyModel::index(int row, int column, const QModelIndex& parent) const
{
  return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QModelIndex ImageWrapProxyModel::parent(const QModelIndex& child) const
{
  Q_UNUSED(child)
  return QModelIndex{};
}

int ImageWrapProxyModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  if (!sourceModel())
  {
    return 0;
  }
  return sourceModel()->rowCount() + m_wrapedTiles;
}

int ImageWrapProxyModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return 1;
}

QModelIndex ImageWrapProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
  if (!sourceModel() || !proxyIndex.isValid())
  {
    return QModelIndex{};
  }
  return index(proxyIndex.row() % sourceModel()->rowCount(), proxyIndex.column());
}

QModelIndex ImageWrapProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
  if (!sourceModel() || !sourceIndex.isValid())
  {
    return QModelIndex{};
  }
  return index(sourceIndex.row(), sourceIndex.column());
}

void ImageWrapProxyModel::setTiledImageModel(TiledImageModel* newTiledImageModel)
{
  if (m_tiledImageModel == newTiledImageModel)
  {
    return;
  }
  m_tiledImageModel = newTiledImageModel;
}

void ImageWrapProxyModel::updateWrapedTiles()
{
  int newWrapedTiles = 0;

  if (m_tiledImageModel && m_tiledImageModel->sourceWidth() > 0)
  {
    qreal sourceWidth = m_tiledImageModel->sourceWidth();

    while (sourceWidth < m_sourceWidth)
    {
      sourceWidth += m_tiledImageModel->tileWidth(newWrapedTiles % m_tiledImageModel->rowCount());
      newWrapedTiles++;
    }
  }

  if (newWrapedTiles > m_wrapedTiles)
  {
    beginInsertRows({}, sourceModel()->rowCount() + m_wrapedTiles, sourceModel()->rowCount() + newWrapedTiles - 1);
    m_wrapedTiles = newWrapedTiles;
    endInsertRows();
  }
  else if (newWrapedTiles < m_wrapedTiles)
  {
    beginRemoveRows({}, sourceModel()->rowCount() + newWrapedTiles, sourceModel()->rowCount() + m_wrapedTiles - 1);
    m_wrapedTiles = newWrapedTiles;
    endRemoveRows();
  }
}

void ImageWrapProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
  beginResetModel();
  auto oldModel = this->sourceModel();

  if (oldModel)
  {
    oldModel->disconnect(this);
  }

  setTiledImageModel(qobject_cast<TiledImageModel*>(sourceModel));

  if (sourceModel)
  {
    connect(sourceModel, &QAbstractItemModel::modelAboutToBeReset, this, &ImageWrapProxyModel::modelAboutToBeReset);
    connect(sourceModel, &QAbstractItemModel::modelReset, this, &ImageWrapProxyModel::modelReset);
  }

  QAbstractProxyModel::setSourceModel(sourceModel);
  updateWrapedTiles();
  endResetModel();
}

qreal ImageWrapProxyModel::sourceWidth() const
{
  return m_sourceWidth;
}

void ImageWrapProxyModel::setSourceWidth(qreal newSourceWidth)
{
  if (qFuzzyCompare(m_sourceWidth, newSourceWidth))
  {
    return;
  }
  m_sourceWidth = newSourceWidth;
  updateWrapedTiles();
  emit sourceWidthChanged();
}

} // namespace wsgui
