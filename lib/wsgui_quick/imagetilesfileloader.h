#pragma once

#include "imagetiles.h"

#include <QObject>
#include <QQmlEngine>

class ImageTilesFileLoader : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(std::vector<QString> fileNames READ fileNames WRITE setFileNames
                 NOTIFY fileNamesChanged FINAL)
  Q_PROPERTY(
      ImageTiles imageTiles READ imageTiles NOTIFY imageTilesChanged FINAL)
  Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)

public:
  explicit ImageTilesFileLoader() = default;

  const std::vector<QString>& fileNames() const;
  void setFileNames(const std::vector<QString>& fileNames);

  const ImageTiles& imageTiles() const;

  int rows() const;
  void setRows(int rows);

signals:
  void fileNamesChanged();
  void imageTilesChanged();
  void rowsChanged();

private:
  void loadImageTiles();

  std::vector<QString> m_fileNames;
  ImageTiles m_imageTiles;
  int m_rows = 1;
};

Q_DECLARE_METATYPE(ImageTiles)
