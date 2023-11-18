#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QSizeF>

namespace wsgui {

class TiledImageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QSizeF sourceSize READ sourceSize NOTIFY sourceSizeChanged)
    QML_ELEMENT
public:
    explicit TiledImageModel(const QString &sourcePrefix = "", QObject *parent = nullptr);

    QSizeF sourceSize() const;

    void updateTiles(const std::vector<QImage> &imageTiles,
                     const QDateTime &imageTime,
                     const QString &resolution);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sourceSizeChanged();

private:
    enum Roles { Source = Qt::UserRole, Width, Height };
    struct ImageTile
    {
        QString source;
        int width = 0;
        int height = 0;
    };

    void setSourceSize(const QSizeF &newSourceSize);

    std::vector<ImageTile> m_tiles;
    QSizeF m_sourceSize;
    QString m_sourcePrefix;
};

} // namespace wsgui
