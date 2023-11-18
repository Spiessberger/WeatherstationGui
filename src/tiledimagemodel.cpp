#include "tiledimagemodel.h"

#include <QImage>

namespace wsgui {

TiledImageModel::TiledImageModel(const QString &sourcePrefix, QObject *parent)
    : QAbstractListModel(parent)
    , m_sourcePrefix(sourcePrefix)
{}

int TiledImageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(m_tiles.size());
}

QVariant TiledImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(m_tiles.size())) {
        return QVariant();
    }

    switch (role) {
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

QSizeF TiledImageModel::sourceSize() const
{
    return m_sourceSize;
}

void TiledImageModel::updateTiles(const std::vector<QImage> &imageTiles,
                                  const QDateTime &imageTime,
                                  const QString &resolution)
{
    beginResetModel();
    m_tiles.clear();

    const QString source = m_sourcePrefix + "/" + imageTime.toString(Qt::ISODate) + "/" + resolution
                           + "/%1";

    QSizeF sourceSize{0, 0};
    for (const QImage &image : imageTiles) {
        ImageTile tile;

        tile.width = image.width();
        tile.height = image.height();
        tile.source = source.arg(m_tiles.size());

        sourceSize.setWidth(sourceSize.width() + image.width());
        sourceSize.setHeight(std::max(image.height(), tile.height));

        m_tiles.push_back(tile);
    }
    endResetModel();
    setSourceSize(sourceSize);
}

void TiledImageModel::setSourceSize(const QSizeF &newSourceSize)
{
    if (m_sourceSize == newSourceSize) {
        return;
    }
    m_sourceSize = newSourceSize;
    emit sourceSizeChanged();
}

} // namespace wsgui
