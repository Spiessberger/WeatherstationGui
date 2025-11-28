#include "imagetiles.h"

#include <QDebug>

bool ImageTiles::isNull() const
{
  return m_imageTiles.empty();
}

int ImageTiles::rowCount() const
{
  return m_imageTiles.size();
}

int ImageTiles::columnCount() const
{
  if (m_imageTiles.empty())
  {
    return 0;
  }
  return m_imageTiles.front().size();
}

QSize ImageTiles::resolution() const
{
  return m_resolution;
}

QImage ImageTiles::imageTile(int row, int column) const
{
  if (row < rowCount() && column < columnCount())
  {
    return m_imageTiles[row][column];
  }
  return QImage{};
}

const std::vector<std::vector<QImage>>& ImageTiles::imageTiles() const
{
  return m_imageTiles;
}

void ImageTiles::setImageTiles(std::vector<std::vector<QImage>> imageTiles)
{
  QSize resolution{0, 0};

  m_imageTiles.clear();
  m_resolution = resolution;

  if (imageTiles.empty())
  {
    return;
  }

  const size_t columnCount = imageTiles.front().size();
  if (columnCount == 0)
  {
    qWarning() << "no images specified in column";
    return;
  }

  for (const std::vector<QImage>& row : imageTiles)
  {
    if (row.size() != columnCount)
    {
      qWarning() << "column count mismatch" << row.size()
                 << "!=" << columnCount;
      return;
    }

    int rowWidth = 0;
    int rowHeight = row.front().height();

    for (const QImage& tile : row)
    {
      if (tile.isNull() || tile.height() <= 0 || tile.width() <= 0)
      {
        qWarning() << "invalid image tile";
        return;
      }
      if (tile.height() != rowHeight)
      {
        qWarning() << "row height mismatch" << tile.height()
                   << "!=" << rowHeight;
        return;
      }
      rowWidth += tile.width();
    }

    if (resolution.width() == 0)
    {
      resolution.setWidth(rowWidth);
    }
    else if (resolution.width() != rowWidth)
    {
      qWarning() << "row width mismatch" << rowWidth
                 << "!=" << resolution.width();
      return;
    }

    resolution.setHeight(resolution.height() + rowHeight);
  }

  m_resolution = resolution;
  m_imageTiles = std::move(imageTiles);
}
