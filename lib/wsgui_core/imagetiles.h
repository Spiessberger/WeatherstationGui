#pragma once

#include <QImage>
#include <vector>

class ImageTiles
{
public:
  ImageTiles() = default;
  ImageTiles(std::vector<std::vector<QImage>> imageTiles);

  bool isNull() const;

  int rowCount() const;
  int columnCount() const;

  QSize resolution() const;

  QImage imageTile(int row, int column) const;

  const std::vector<std::vector<QImage>>& imageTiles() const;
  void setImageTiles(std::vector<std::vector<QImage>> imageTiles);

private:
  std::vector<std::vector<QImage>> m_imageTiles;
  QSize m_resolution;
};
