#pragma once

#include <QAbstractProxyModel>
#include <QQmlEngine>

#include "tiledimagemodel.h"

namespace wsgui {

class ImageWrapProxyModel : public QAbstractProxyModel
{
  Q_OBJECT
  Q_PROPERTY(qreal sourceWidth READ sourceWidth WRITE setSourceWidth NOTIFY sourceWidthChanged)
  QML_ELEMENT
public:
  ImageWrapProxyModel();

  void setSourceModel(QAbstractItemModel* sourceModel) override;
  QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
  QModelIndex parent(const QModelIndex& child) const override;
  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;

  QModelIndex mapToSource(const QModelIndex& proxyIndex) const override;
  QModelIndex mapFromSource(const QModelIndex& sourceIndex) const override;

  qreal sourceWidth() const;
  void setSourceWidth(qreal newSourceWidth);

signals:
  void sourceWidthChanged();

private:
  void setTiledImageModel(TiledImageModel* newTiledImageModel);
  void updateWrapedTiles();

  TiledImageModel* m_tiledImageModel = nullptr;
  qreal m_sourceWidth = 0.0;
  int m_wrapedTiles = 0;
};

} // namespace wsgui
