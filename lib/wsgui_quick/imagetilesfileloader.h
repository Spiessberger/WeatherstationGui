#pragma once

#include <imagetiles.h>

#include <QObject>
#include <QQmlEngine>

namespace wsgui::quick
{

class ImageTilesFileLoader : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(std::vector<QString> fileNames READ fileNames WRITE setFileNames
                 NOTIFY fileNamesChanged FINAL)
  Q_PROPERTY(wsgui::core::ImageTiles imageTiles READ imageTiles NOTIFY
                 imageTilesChanged FINAL)
  Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)

public:
  explicit ImageTilesFileLoader() = default;

  const std::vector<QString>& fileNames() const;
  void setFileNames(const std::vector<QString>& fileNames);

  const core::ImageTiles& imageTiles() const;

  int rows() const;
  void setRows(int rows);

signals:
  void fileNamesChanged();
  void imageTilesChanged();
  void rowsChanged();

private:
  void loadImageTiles();

  std::vector<QString> m_fileNames;
  core::ImageTiles m_imageTiles;
  int m_rows = 1;
};

} // namespace wsgui::quick

Q_DECLARE_METATYPE(wsgui::core::ImageTiles)
