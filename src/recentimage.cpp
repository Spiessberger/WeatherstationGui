#include "recentimage.h"

#include <QLoggingCategory>

#include <unordered_set>

#include "imagesize.h"

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::panomax::RecentImage")
}

namespace wsgui
{
namespace panomax
{

RecentImage::RecentImage(QObject* parent)
    : QObject{parent}
{
  connect(&m_dayInfoUpdateTimer, &QTimer::timeout, this, &RecentImage::updateDayInfo);
  connect(&m_imageDownloader,
          &ImageDownloader::finished,
          this,
          &RecentImage::imageDownloadFinished);
  connect(&m_imageDownloader,
          &DayInfoDownloader::failed,
          this,
          [this]()
          {
            m_downloadInfo = {};
            emit imageDownloadFailed();
          });
  connect(&m_imageDownloader,
          &ImageDownloader::progressChanged,
          this,
          &RecentImage::progressChanged);
  connect(&m_dayInfoDownloader,
          &DayInfoDownloader::finished,
          this,
          &RecentImage::dayInfoDownloadFinished);
  connect(&m_dayInfoDownloader,
          &DayInfoDownloader::failed,
          this,
          &RecentImage::dayInfoDownloadFailed);
}

int RecentImage::camId() const
{
  return m_camId;
}

void RecentImage::setCamId(int newCamId)
{
  if (m_camId == newCamId)
  {
    return;
  }
  m_camId = newCamId;
  emit camIdChanged();

  updateDayInfo();
  if (m_dayInfoUpdateTimer.isActive())
  {
    m_dayInfoUpdateTimer.start(m_updateInterval);
  }
}

int RecentImage::updateIntervalMs() const
{
  return m_updateInterval.count();
}

void RecentImage::setUpdateIntervalMs(int newUpdateIntervalMs)
{
  if (m_updateInterval.count() == newUpdateIntervalMs)
  {
    return;
  }
  m_updateInterval = std::chrono::milliseconds{newUpdateIntervalMs};
  emit updateIntervalChanged();

  m_dayInfoUpdateTimer.start(m_updateInterval);
}

std::vector<ImageResolution> RecentImage::imageResolutions() const
{
  return m_imageResolutions;
}

void RecentImage::setImageResolutions(const std::vector<ImageResolution>& newImageResolutions)
{
  if (m_imageResolutions == newImageResolutions)
  {
    return;
  }
  m_imageResolutions = newImageResolutions;
  emit imageResolutionsChanged();

  updateResolutionQueue();
}

const std::vector<QImage>& RecentImage::imageTiles() const
{
  return m_imageTiles;
}

int RecentImage::progress() const
{
  return m_imageDownloader.progress();
}

void RecentImage::updateDayInfo()
{
  if (m_dayInfoDownloader.downloading())
  {
    qCDebug(log) << "aborting running day info download";
    m_dayInfoDownloader.abort();
  }
  m_dayInfoDownloader.download(m_camId);
}

void RecentImage::imageDownloadFinished()
{
  m_imageTiles = m_imageDownloader.imageTiles();
  m_tilesInfo = m_downloadInfo;
  m_downloadInfo = {};
  emit imageTilesChanged();
  if (!m_imageResolutionQueue.empty())
  {
    downloadImageTiles();
  }
}

void RecentImage::dayInfoDownloadFinished()
{
  const DayInfo& dayInfo = m_dayInfoDownloader.dayInfo();

  if (dayInfo.imageTimes.empty())
  {
    qCWarning(log) << "no image times";
    return;
  }

  const QDateTime imageTime{dayInfo.date, dayInfo.imageTimes.back()};
  if (imageTime <= m_tilesInfo.time
      || (imageTime <= m_downloadInfo.time && m_imageDownloader.downloading()))
  {
    qCDebug(log) << "no new image to download";
    return;
  }
  m_imageDownloader.abort();

  updateResolutionQueue();
  downloadImageTiles();
}

void RecentImage::updateResolutionQueue()
{
  // clear current resolution queue
  while (!m_imageResolutionQueue.empty())
  {
    m_imageResolutionQueue.pop();
  }
  std::unordered_set<ImageResolution> resolutions;

  for (ImageResolution resolution: m_imageResolutions)
  {
    const bool inserted = resolutions.insert(resolution).second;
    if (inserted)
    {
      m_imageResolutionQueue.push(resolution);
    }
  }
}

void RecentImage::downloadImageTiles()
{
  const DayInfo& dayInfo = m_dayInfoDownloader.dayInfo();
  if (dayInfo.date.isNull() || dayInfo.imageTimes.empty())
  {
    qCWarning(log) << "no image time to download";
    return;
  }

  if (m_imageResolutionQueue.empty())
  {
    qCWarning(log) << "no resolution to download in queue";
    return;
  }

  ImageSize imageSize;

  while (!m_imageResolutionQueue.empty() && imageSize.resolution == ImageResolution::None)
  {
    const ImageResolution resolution = m_imageResolutionQueue.front();
    m_imageResolutionQueue.pop();
    auto iter = std::ranges::find_if(dayInfo.imageSizes,
                                     [resolution](const ImageSize& imageSize)
                                     { return imageSize.resolution == resolution; });
    if (iter != dayInfo.imageSizes.end())
    {
      imageSize = *iter;
    }
    else
    {
      qCWarning(log) << "cannot find image size for resolution" << resolution;
    }
  }

  if (imageSize.resolution == ImageResolution::None)
  {
    qCWarning(log) << "no image size to download";
    return;
  }

  const QDateTime imageTime{dayInfo.date, dayInfo.imageTimes.back()};
  m_downloadInfo.time = imageTime;
  m_downloadInfo.resolution = imageSize.resolution;

  if (m_imageDownloader.downloading())
  {
    qCDebug(log) << "aborting running image download";
    m_imageDownloader.abort();
  }

  m_imageDownloader.download(m_camId, imageSize, imageTime);
}

} // namespace panomax
} // namespace wsgui
