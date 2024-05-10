#include "imagedownloader.h"

#include <QLoggingCategory>

#include "jsonserializeimageresolution.h"

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::panomax::ImageDownloader")
}

namespace wsgui
{
namespace panomax
{

ImageDownloader::ImageDownloader(QObject* parent)
    : Downloader(parent)
{
}

bool ImageDownloader::download(int camId, const ImageSize& imageSize, const QDateTime& imageTime)
{
  // %1 = camId
  // %2 = image time in format yyyy/MM/dd/HH-mm-ss
  // %3 = image resolution
  static const QString urlTemplate =
      QStringLiteral("https://panodata.panomax.com/cams/%1/%2_%3.jpg");
  static const QString dateTimeFormat = QStringLiteral("yyyy/MM/dd/HH-mm-ss");

  if (downloading())
  {
    qCWarning(log) << "Download already in progress";
    return false;
  }

  if (imageSize.columns < 1)
  {
    qCWarning(log) << "Invalid number of tiles to download" << m_tilesToDownload;
    return false;
  }

  nlohmann::json j = imageSize.resolution;
  const QString resolutionString = QString::fromStdString(j);
  if (resolutionString.isEmpty())
  {
    qCWarning(log) << "Invalid resolution" << imageSize.resolution;
    return false;
  }

  m_tilesToDownload = imageSize.columns;
  m_imageTiles.clear();

  QString resolutionTemplate = resolutionString;
  if (m_tilesToDownload > 1)
  {
    resolutionTemplate += QStringLiteral("_%3_0");
    // for some reason there is one more image to download than specified in the info
    m_tilesToDownload++;
  }

  m_urlTemplate =
      urlTemplate.arg(camId).arg(imageTime.toString(dateTimeFormat)).arg(resolutionTemplate);

  return downloadNextTile();
}

Downloader::DownloadState ImageDownloader::downloadDone(const QByteArray& data)
{
  QImage tile = QImage::fromData(data);

  if (tile.isNull())
  {
    qCWarning(log) << "failed to read image from" << data.size() << "data bytes";
    return DownloadState::Failed;
  }

  m_imageTiles.push_back(tile);

  if (m_imageTiles.size() < m_tilesToDownload)
  {
    downloadNextTile();
    return DownloadState::Continue;
  }
  return DownloadState::Finished;
}

void ImageDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  int progress = 0;

  if (m_tilesToDownload > 0)
  {
    if (bytesTotal > 0)
    {
      progress = 100 * bytesReceived / bytesTotal / m_tilesToDownload;
    }
    progress += 100 * m_imageTiles.size() / m_tilesToDownload;
  }

  setProgress(progress);
}

bool ImageDownloader::downloadNextTile()
{
  QUrl url;
  if (m_tilesToDownload > 1)
  {
    url = m_urlTemplate.arg(m_imageTiles.size());
  }
  else
  {
    url = m_urlTemplate;
  }
  return startDownload(url);
}

const std::vector<QImage>& ImageDownloader::imageTiles() const
{
  return m_imageTiles;
}

} // namespace panomax
} // namespace wsgui
