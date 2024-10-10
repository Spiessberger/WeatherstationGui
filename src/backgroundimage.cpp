#include "backgroundimage.h"

#include <QLoggingCategory>

#include <unordered_set>

#include "imagesize.h"

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::panomax::BackgroundImage")
}

namespace wsgui
{
namespace panomax
{

BackgroundImage::BackgroundImage(QObject* parent)
    : QObject{parent}
{
  connect(&m_dayInfoUpdateTimer,
          &QTimer::timeout,
          &m_recentImageInfo,
          &RecentImageInfo::updateDayInfo);
  connect(&m_imageDownloader,
          &ImageDownloader::finished,
          this,
          &BackgroundImage::imageDownloadFinished);
  connect(&m_imageDownloader,
          &ImageDownloader::failed,
          this,
          [this]()
          {
            m_downloadInfo = {};
            emit imageDownloadFailed();
          });
  connect(&m_imageDownloader,
          &ImageDownloader::progressChanged,
          this,
          &BackgroundImage::progressChanged);
  connect(&m_recentImageInfo,
          &RecentImageInfo::recentImageInfoChanged,
          this,
          &BackgroundImage::restartImageTilesDownload);
  connect(&m_recentImageInfo,
          &RecentImageInfo::dayInfoDownloadFailed,
          this,
          &BackgroundImage::dayInfoDownloadFailed);
}

int BackgroundImage::camId() const
{
  return m_camId;
}

void BackgroundImage::setCamId(int newCamId)
{
  if (m_camId == newCamId)
  {
    return;
  }
  m_camId = newCamId;
  emit camIdChanged();

  m_recentImageInfo.setCamId(m_camId);
  m_recentImageInfo.updateDayInfo();
  if (m_camId != 0)
  {
    m_dayInfoUpdateTimer.start(m_updateInterval);
  }
  else
  {
    m_dayInfoUpdateTimer.stop();
  }
}

int BackgroundImage::updateIntervalMs() const
{
  return m_updateInterval.count();
}

void BackgroundImage::setUpdateIntervalMs(int newUpdateIntervalMs)
{
  if (m_updateInterval.count() == newUpdateIntervalMs)
  {
    return;
  }
  m_updateInterval = std::chrono::milliseconds{newUpdateIntervalMs};
  emit updateIntervalChanged();

  if (m_camId != 0)
  {
    m_dayInfoUpdateTimer.start(m_updateInterval);
  }
}

std::vector<ImageResolution> BackgroundImage::imageResolutions() const
{
  return m_imageResolutions;
}

void BackgroundImage::setImageResolutions(const std::vector<ImageResolution>& newImageResolutions)
{
  if (m_imageResolutions == newImageResolutions)
  {
    return;
  }
  m_imageResolutions = newImageResolutions;
  emit imageResolutionsChanged();

  if (!m_recentImageInfo.recentImageTime().isNull() && !m_recentImageInfo.imageSizes().empty())
  {
    restartImageTilesDownload();
  }
}

const std::vector<QImage>& BackgroundImage::thumbImageTiles() const
{
  return m_thumbImageTiles;
}

const std::vector<QImage>& BackgroundImage::imageTiles() const
{
  return m_imageTiles;
}

int BackgroundImage::progress() const
{
  return m_imageDownloader.progress();
}

void BackgroundImage::imageDownloadFinished()
{
  qCDebug(log) << "finished image tiles download of resolution" << m_downloadInfo.resolution;

  if (m_downloadInfo.resolution == m_thumbResolution)
  {
    m_thumbImageTiles = m_imageDownloader.imageTiles();
    emit thumbImageTilesChanged();
    qCDebug(log) << "updated thumb tiles";
  }

  if (m_downloadInfo.resolution != m_thumbResolution
      || std::ranges::find(m_imageResolutions, m_thumbResolution) != m_imageResolutions.end())
  {
    m_imageTiles = m_imageDownloader.imageTiles();
    emit imageTilesChanged();
    qCDebug(log) << "updated image tiles";
  }

  m_tilesInfo = m_downloadInfo;
  m_downloadInfo = {};
  if (!m_imageResolutionQueue.empty())
  {
    downloadImageTiles();
  }
}

void BackgroundImage::restartImageTilesDownload()
{
  m_imageDownloader.abort();
  updateResolutionQueue();
  downloadImageTiles();
}

void BackgroundImage::updateResolutionQueue()
{
  // clear current resolution queue
  m_imageResolutionQueue = {};
  std::unordered_set<ImageResolution> resolutions;

  if (m_thumbResolution != ImageResolution::None)
  {
    auto thumbIter = std::ranges::find_if(m_recentImageInfo.imageSizes(),
                                          [this](const ImageSize& imageSize)
                                          { return imageSize.resolution == m_thumbResolution; });

    if (thumbIter != m_recentImageInfo.imageSizes().end())
    {
      resolutions.insert(m_thumbResolution);
      m_imageResolutionQueue.push(m_thumbResolution);
    }
    else
    {
      qCWarning(log) << "reqested thumbnail resolution" << m_thumbResolution << "is not available";
    }
  }

  for (ImageResolution resolution: m_imageResolutions)
  {
    const bool inserted = resolutions.insert(resolution).second;
    if (inserted)
    {
      m_imageResolutionQueue.push(resolution);
    }
  }
}

void BackgroundImage::downloadImageTiles()
{
  if (m_recentImageInfo.recentImageTime().isNull())
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
    auto iter = std::ranges::find_if(m_recentImageInfo.imageSizes(),
                                     [resolution](const ImageSize& imageSize)
                                     { return imageSize.resolution == resolution; });
    if (iter != m_recentImageInfo.imageSizes().end())
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

  m_downloadInfo.time = m_recentImageInfo.recentImageTime();
  m_downloadInfo.resolution = imageSize.resolution;

  if (m_imageDownloader.downloading())
  {
    qCDebug(log) << "aborting running image download";
    m_imageDownloader.abort();
  }

  m_imageDownloader.download(m_camId, imageSize, m_recentImageInfo.recentImageTime());
}

wsgui::panomax::ImageResolution BackgroundImage::thumbResolution() const
{
  return m_thumbResolution;
}

void BackgroundImage::setThumbResolution(const wsgui::panomax::ImageResolution& newThumbResolution)
{
  if (m_thumbResolution == newThumbResolution)
  {
    return;
  }
  m_thumbResolution = newThumbResolution;
  emit thumbResolutionChanged();
}

} // namespace panomax
} // namespace wsgui
