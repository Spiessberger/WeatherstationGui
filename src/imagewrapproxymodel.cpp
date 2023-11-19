#include "imagewrapproxymodel.h"

namespace wsgui {

ImageWrapProxyModel::ImageWrapProxyModel() {}

QModelIndex ImageWrapProxyModel::index(int row, int column,
                                       const QModelIndex &parent) const {
  return hasIndex(row, column, parent) ? createIndex(row, column)
                                       : QModelIndex();
}

QModelIndex ImageWrapProxyModel::parent(const QModelIndex &child) const {
  Q_UNUSED(child)
  return QModelIndex{};
}

int ImageWrapProxyModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  if (!sourceModel()) {
    return 0;
  }
  return sourceModel()->rowCount();
}

int ImageWrapProxyModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return 1;
}

QModelIndex
ImageWrapProxyModel::mapToSource(const QModelIndex &proxyIndex) const {
  if (!sourceModel()) {
    return QModelIndex{};
  }
  return createIndex(proxyIndex.row(), proxyIndex.column());
}

QModelIndex
ImageWrapProxyModel::mapFromSource(const QModelIndex &sourceIndex) const {
  if (!sourceModel()) {
    return QModelIndex{};
  }
  return createIndex(sourceIndex.row(), sourceIndex.column());
}

TiledImageModel *ImageWrapProxyModel::tiledImageModel() const {
  return m_tiledImageModel;
}

void ImageWrapProxyModel::setTiledImageModel(
    TiledImageModel *newTiledImageModel) {
  setSourceModel(newTiledImageModel);
  if (m_tiledImageModel == newTiledImageModel) {
    return;
  }
  m_tiledImageModel = newTiledImageModel;
  emit tiledImageModelChanged();
}

qreal ImageWrapProxyModel::sourceWidth() const { return m_sourceWidth; }

void ImageWrapProxyModel::setSourceWidth(qreal newSourceWidth) {
  if (qFuzzyCompare(m_sourceWidth, newSourceWidth)) {
    return;
  }
  m_sourceWidth = newSourceWidth;
  emit sourceWidthChanged();
}

} // namespace wsgui
