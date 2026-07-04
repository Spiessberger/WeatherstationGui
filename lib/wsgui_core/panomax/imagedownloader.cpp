#include "imagedownloader.h"

namespace wsgui::core::panomax
{
namespace
{
const QString ApiUrlTemplate =
    QStringLiteral("https://panodata.panomax.com/cams/%1/%2_%3.jpg");
const QString ApiDateTimeTemplate = QStringLiteral("yyyy/MM/dd/HH-mm-ss");
const QString ApiTileTemplate = QStringLiteral("%1_%2_%3");
} // namespace

ImageDownloader::ImageDownloader(Downloader& downloader)
  : m_downloader(downloader)
{
}

QtPromise::QPromise<ImageTiles>
ImageDownloader::download(int camId, const QDateTime& dateTime,
                          const ImageSize& size)
{
  const int columns = size.cols > 1 ? size.cols + 1 : size.cols;
  const int rows = size.rows > 1 ? size.rows + 1 : size.rows;

  if (columns < 1 || rows < 1)
  {
    return QtPromise::QPromise<ImageTiles>::reject("");
  }

  std::vector<QtPromise::QPromise<QByteArray>> promises;

  if (columns == 1 && rows == 1)
  {
    QString url = ApiUrlTemplate.arg(camId)
                      .arg(dateTime.toString(ApiDateTimeTemplate))
                      .arg(size.resolution);

    promises.push_back(m_downloader.download(url));
  }
  else
  {
    for (int row = 0; row < rows; row++)
    {
      for (int column = 0; column < columns; column++)
      {
        QString tile =
            ApiTileTemplate.arg(size.resolution).arg(column).arg(row);
        QString url = ApiUrlTemplate.arg(camId).arg(
            dateTime.toString(ApiDateTimeTemplate), tile);

        promises.push_back(m_downloader.download(url));
      }
    }
  }

  return QtPromise::all(promises).then(
      [columns](const QVector<QByteArray>& data)
      {
        int column = 0;
        std::vector<std::vector<QImage>> tiles;
        std::vector<QImage> row;
        for (const QByteArray& imageData : data)
        {
          QImage image = QImage::fromData(imageData);
          if (image.isNull())
          {
            qWarning() << "failed to load iamge tile";
            throw "";
          }
          row.push_back(image);
          column++;

          if (column == columns)
          {
            tiles.push_back(std::move(row));
            column = 0;
          }
        }

        return ImageTiles{std::move(tiles)};
      });
}

} // namespace wsgui::core::panomax
