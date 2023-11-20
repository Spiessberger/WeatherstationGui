#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

namespace wsgui {

class TiledImageModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(qreal sourceWidth READ sourceWidth WRITE setSourceWidth NOTIFY
                 sourceWidthChanged)
  Q_PROPERTY(qreal sourceHeight READ sourceHeight WRITE setSourceHeight NOTIFY
                 sourceHeightChanged)
  QML_ELEMENT
public:
  explicit TiledImageModel(const QString &sourcePrefix = "",
                           QObject *parent = nullptr);

  qreal sourceWidth() const;
  qreal sourceHeight() const;

  int tileWidth(int index) const;
  int tileHeight(int index) const;
  void updateTiles(const std::vector<QImage> &imageTiles,
                   const QDateTime &imageTime, const QString &resolution);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

signals:
  void sourceWidthChanged();
  void sourceHeightChanged();

private:
  enum Roles { Source = Qt::UserRole, Width, Height };
  struct ImageTile {
    QString source;
    int width = 0;
    int height = 0;
  };

  void setSourceWidth(qreal newSourceWidth);
  void setSourceHeight(qreal newSourceHeight);

  qreal m_sourceWidth = 0.0;
  qreal m_sourceHeight = 0.0;
  std::vector<ImageTile> m_tiles;
  QString m_sourcePrefix;
};

} // namespace wsgui
