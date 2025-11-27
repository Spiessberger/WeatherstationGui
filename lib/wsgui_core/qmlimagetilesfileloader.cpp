#include "qmlimagetilesfileloader.h"

#include <QQmlFile>

const std::vector<QString>& QmlImageTilesFileLoader::fileNames() const
{
  return m_fileNames;
}

void QmlImageTilesFileLoader::setFileNames(
    const std::vector<QString>& fileNames)
{
  if (m_fileNames == fileNames)
  {
    return;
  }
  m_fileNames = fileNames;
  emit fileNamesChanged();

  loadImageTiles();
}

const ImageTiles& QmlImageTilesFileLoader::imageTiles() const
{
  return m_imageTiles;
}

void QmlImageTilesFileLoader::loadImageTiles()
{
  if (m_rows < 1 || m_fileNames.size() % m_rows != 0)
  {
    qWarning() << "cannot populate" << m_rows << "with" << m_fileNames.size()
               << "image files";
    return;
  }

  const size_t numColumns = m_fileNames.size() / m_rows;

  std::vector<std::vector<QImage>> tiles;

  std::vector<QImage> row;
  for (const QString& fileName : m_fileNames)
  {
    QImage tile;

    if (QQmlFile::isLocalFile(fileName))
    {
      QString localFilePath = QQmlFile::urlToLocalFileOrQrc(fileName);
      tile.load(localFilePath);
    }
    else
    {
      tile.load(fileName);
    }

    if (tile.isNull())
    {
      qWarning() << "failed to load image" << fileName;
      return;
    }

    row.push_back(std::move(tile));

    if (row.size() == numColumns)
    {
      tiles.push_back(std::move(row));
    }
  }

  m_imageTiles.setImageTiles(tiles);
  emit imageTilesChanged();
}

int QmlImageTilesFileLoader::rows() const
{
  return m_rows;
}

void QmlImageTilesFileLoader::setRows(int rows)
{
  if (m_rows == rows)
  {
    return;
  }
  m_rows = rows;
  emit rowsChanged();

  loadImageTiles();
}
