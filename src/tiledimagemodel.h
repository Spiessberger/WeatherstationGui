#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QSize>

namespace wsgui {

class TiledImageModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(QSizeF sourceSize READ sourceSize WRITE setSourceSize NOTIFY sourceSizeChanged)
  QML_ELEMENT
public:
  struct ImageTile
  {
    QString source;
    int width = 0;
    int height = 0;
  };

  explicit TiledImageModel(QObject* parent = nullptr);

  QSizeF sourceSize() const;

  int tileWidth(int index) const;
  int tileHeight(int index) const;
  void setTiles(const std::vector<ImageTile>& imageTiles);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

signals:
  void sourceSizeChanged();

private:
  enum Roles { Source = Qt::UserRole, Width, Height };

  void setSourceSize(const QSizeF& newSourceSize);

  std::vector<ImageTile> m_tiles;
  QSizeF m_sourceSize;
};

} // namespace wsgui
