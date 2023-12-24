#include "panomaximage.h"

namespace wsgui {
namespace panomax {

// %1 = camId
// %2 = image time in format yyyy/MM/dd/HH-mm-ss
// %3 = image resolution
static const QString urlTemplate = QStringLiteral("https://panodata8.panomax.com/cams/%1/%2_%3.jpg");

PanomaxImage::PanomaxImage(QObject* parent) : QObject{parent}
{
}

QString PanomaxImage::camId() const
{
  return m_camId;
}

void PanomaxImage::setCamId(const QString& newCamId)
{
  if (m_camId == newCamId)
  {
    return;
  }
  m_camId = newCamId;
}

QDateTime PanomaxImage::imageTime() const
{
  return m_imageTime;
}

void PanomaxImage::setImageTime(const QDateTime& newImageTime)
{
  if (m_imageTime == newImageTime)
  {
    return;
  }
  m_imageTime = newImageTime;
}

std::vector<PanomaxImageSize> PanomaxImage::requestedImageSizes() const
{
  return m_requestedImageSizes;
}

void PanomaxImage::setRequestedImageSizes(const std::vector<PanomaxImageSize>& newRequestedImageSizes)
{
  m_requestedImageSizes = newRequestedImageSizes;
  // TODO: download new sizes, remove obsolete sizes
}

bool PanomaxImage::isAvailable(PanomaxImageSize::Resolution resolution) const
{
  return std::find_if(m_images.cbegin(), m_images.cend(), [resolution](const auto& image) {
           return image.resolution == resolution;
         }) != m_images.cend();
}

std::vector<PanomaxImageSize::Resolution> PanomaxImage::availableResolutions() const
{
  std::vector<PanomaxImageSize::Resolution> ret;

  for (const auto& image : m_images)
  {
    ret.push_back(image.resolution);
  }

  return ret;
}

std::vector<QImage> PanomaxImage::image(PanomaxImageSize::Resolution resolution) const
{
  for (const auto& image : m_images)
  {
    if (image.resolution == resolution)
    {
      return image.tiles;
    }
  }
  return std::vector<QImage>{};
}

void PanomaxImage::updateImages()
{
  // reset everything
  m_images.clear();
  if (!m_currentDownload.reply.isNull())
  {
    qDebug() << "aborting running tile download";
    disconnect(m_currentDownload.reply, &QNetworkReply::finished, this, &PanomaxImage::downloadFinished);
    m_currentDownload.reply->abort();
  }

  for (const PanomaxImageSize& imageSize : m_requestedImageSizes)
  {
    m_downloadQueue.push(imageSize);
  }

  downloadNextImage();
}

void PanomaxImage::downloadNextImage()
{
  // nothing to download
  if (m_downloadQueue.empty() || m_camId.isEmpty() || m_imageTime.isNull())
  {
    return;
  }

  // clear previous image download
  m_currentDownload.tilesData.clear();
  m_currentDownload.failCounter = 0;

  // skip already downloaded images
  while (!m_downloadQueue.empty() && isAvailable(m_downloadQueue.front().resolution()))
  {
    m_downloadQueue.pop();
  }
  if (!m_downloadQueue.empty())
  {
    m_currentDownload.imageSize = m_downloadQueue.front();
    m_downloadQueue.pop();
    downloadNextTile();
  }
}

void PanomaxImage::downloadNextTile()
{
  // nothing to download
  if (m_currentDownload.imageSize.resolution() == PanomaxImageSize::None || m_camId.isEmpty() || m_imageTime.isNull() ||
      m_currentDownload.imageSize.numTiles() <= 0 ||
      m_currentDownload.tilesData.size() >= m_currentDownload.imageSize.numTiles())
  {
    return;
  }

  if (m_currentDownload.failCounter > 3)
  {
    qWarning() << "download failed too often, aborting";
    downloadNextImage();
    return;
  }

  QString tileQuery = PanomaxImageSize::resolutionToString(m_currentDownload.imageSize.resolution());
  if (m_currentDownload.imageSize.numTiles() > 1)
  {
    tileQuery += QString{"_%1_0"}.arg(m_currentDownload.tilesData.size());
  }
  QString url = urlTemplate.arg(m_camId).arg(m_imageTime.toString("yyyy/MM/dd/HH-mm-ss")).arg(tileQuery);

  qDebug() << "starting download of" << url;
  QNetworkRequest req{url};
  m_currentDownload.reply = m_netManager.get(req);

  connect(m_currentDownload.reply, &QNetworkReply::finished, m_currentDownload.reply, &QNetworkReply::deleteLater);
  connect(m_currentDownload.reply, &QNetworkReply::finished, this, &PanomaxImage::downloadFinished);
}

void PanomaxImage::downloadFinished()
{
  if (m_currentDownload.reply.isNull())
  {
    qWarning() << "download reply is null";
    return;
  }

  if (m_currentDownload.reply->error() != QNetworkReply::NoError)
  {
    m_currentDownload.failCounter++;
    qWarning() << "download failed:" << m_currentDownload.reply->errorString();
    qWarning() << "fail counter:" << m_currentDownload.failCounter;
  }
  else
  {
    m_currentDownload.failCounter = 0;
    m_currentDownload.tilesData.push_back(m_currentDownload.reply->readAll());
  }

  if (m_currentDownload.tilesData.size() < m_currentDownload.imageSize.numTiles())
  {
    downloadNextTile();
  }
  else
  {
    Image newImage;
    newImage.resolution = m_currentDownload.imageSize.resolution();
    qDebug() << "Download of image with resolution" << PanomaxImageSize::resolutionToString(newImage.resolution)
             << "finished";
    for (QByteArray& tileData : m_currentDownload.tilesData)
    {
      QImage tile = QImage::fromData(tileData);
      tileData.clear();
      if (tile.isNull())
      {
        qWarning() << "failed to load tile with index" << newImage.tiles.size();
        newImage.tiles.clear();
        break;
      }
      newImage.tiles.push_back(tile);
    }
    m_currentDownload.tilesData.clear();

    if (!newImage.tiles.empty())
    {
      m_images.push_back(newImage);
    }

    downloadNextImage();
  }
}

} // namespace panomax
} // namespace wsgui
