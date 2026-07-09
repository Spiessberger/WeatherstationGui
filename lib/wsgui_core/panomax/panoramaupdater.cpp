#include "panoramaupdater.h"

#include <algorithm>

#include <QNetworkReply>
#include <QPointer>

#include <logging.h>

namespace wsgui::core::panomax
{
namespace
{
constexpr std::chrono::minutes DefaultUpdateInterval{1};

const ImageSize* findImageSize(const DayImageData& dayImageData,
                               const QString& resolution)
{
  const auto it = std::ranges::find(
      dayImageData.sizes, resolution.toStdString(), &ImageSize::resolution);
  return it != dayImageData.sizes.end() ? &*it : nullptr;
}
} // namespace

PanoramaUpdater::PanoramaUpdater(Downloader& downloader, QObject* parent)
  : QObject(parent), m_dayImageDataDownloader(downloader),
    m_imageDownloader(downloader)
{
  m_timer.setInterval(DefaultUpdateInterval);
  connect(&m_timer, &QTimer::timeout, this, &PanoramaUpdater::checkForNewImage);
}

int PanoramaUpdater::camId() const
{
  return m_camId;
}

void PanoramaUpdater::setCamId(int camId)
{
  if (m_camId == camId)
    return;

  m_camId = camId;
  restartIfRunning();
}

const QString& PanoramaUpdater::resolution() const
{
  return m_resolution;
}

void PanoramaUpdater::setResolution(const QString& resolution)
{
  if (m_resolution == resolution)
    return;

  m_resolution = resolution;
  restartIfRunning();
}

const QString& PanoramaUpdater::fallbackResolution() const
{
  return m_fallbackResolution;
}

void PanoramaUpdater::setFallbackResolution(const QString& fallbackResolution)
{
  if (m_fallbackResolution == fallbackResolution)
    return;

  m_fallbackResolution = fallbackResolution;
  restartIfRunning();
}

std::chrono::milliseconds PanoramaUpdater::updateInterval() const
{
  return m_timer.intervalAsDuration();
}

void PanoramaUpdater::setUpdateInterval(
    std::chrono::milliseconds updateInterval)
{
  m_timer.setInterval(updateInterval);
}

bool PanoramaUpdater::isRunning() const
{
  return m_running;
}

void PanoramaUpdater::start()
{
  if (m_running)
    return;

  m_running = true;
  m_timer.start();
  checkForNewImage();
}

void PanoramaUpdater::stop()
{
  if (!m_running)
    return;

  m_running = false;
  m_timer.stop();
  m_runId++;
  m_updateInFlight = false;
}

const ImageTiles& PanoramaUpdater::imageTiles() const
{
  return m_imageTiles;
}

void PanoramaUpdater::restartIfRunning()
{
  m_latestImageDateTime = {};
  if (!m_running)
    return;

  m_runId++;
  m_updateInFlight = false;
  m_timer.start();
  checkForNewImage();
}

void PanoramaUpdater::checkForNewImage()
{
  if (m_updateInFlight)
  {
    qCDebug(lcPanomax)
        << "skipping update tick, previous update still in flight";
    return;
  }
  m_updateInFlight = true;

  const QPointer<PanoramaUpdater> self{this};
  const int runId = m_runId;

  downloadDayImageData()
      .then(
          [self, runId](const DayImageData& dayImageData)
              -> QtPromise::QPromise<std::optional<PendingImage>>
          {
            if (!self || runId != self->m_runId)
              return QtPromise::QPromise<std::optional<PendingImage>>::resolve(
                  std::optional<PendingImage>{});
            return self->downloadLatestImage(dayImageData);
          })
      .then(
          [self, runId](const std::optional<PendingImage>& pendingImage)
          {
            if (!pendingImage || !self || runId != self->m_runId)
              return;

            self->m_latestImageDateTime = pendingImage->dateTime;
            self->m_imageTiles = pendingImage->imageTiles;
            qCDebug(lcPanomax)
                << "new panorama image" << pendingImage->dateTime;
            emit self->imageTilesChanged(self->m_imageTiles);
          })
      .fail(
          [self, runId](QNetworkReply::NetworkError networkError)
          {
            qCWarning(lcPanomax)
                << "panorama update failed, network error:" << networkError;
            if (self && runId == self->m_runId)
              emit self->errorOccurred(Error::DownloadFailed);
          })
      .fail(
          [self, runId](DayImageDataDownloader::Error)
          {
            qCWarning(lcPanomax)
                << "panorama update failed, could not parse day image data";
            if (self && runId == self->m_runId)
              emit self->errorOccurred(Error::MetadataParsingFailed);
          })
      .fail(
          [self, runId](ImageDownloader::Error error)
          {
            qCWarning(lcPanomax)
                << "panorama update failed, could not load image tiles:"
                << static_cast<int>(error);
            if (self && runId == self->m_runId)
              emit self->errorOccurred(Error::ImageLoadingFailed);
          })
      .fail(
          [self, runId]()
          {
            qCWarning(lcPanomax) << "panorama update failed, unexpected error";
            if (self && runId == self->m_runId)
              emit self->errorOccurred(Error::DownloadFailed);
          })
      .finally(
          [self, runId]()
          {
            if (self && runId == self->m_runId)
              self->m_updateInFlight = false;
          });
}

QtPromise::QPromise<DayImageData> PanoramaUpdater::downloadDayImageData()
{
  const QPointer<PanoramaUpdater> self{this};
  const int runId = m_runId;

  return m_dayImageDataDownloader.download(m_camId).then(
      [self, runId](
          const DayImageData& dayImageData) -> QtPromise::QPromise<DayImageData>
      {
        if (!dayImageData.images.empty() || !self || runId != self->m_runId)
          return QtPromise::QPromise<DayImageData>::resolve(dayImageData);

        // shortly after midnight the current day may have no images yet
        const QDate date = dayImageData.date.isValid() ? dayImageData.date
                                                       : QDate::currentDate();
        qCDebug(lcPanomax) << "no images for" << date
                           << "yet, falling back to the previous day";
        return self->m_dayImageDataDownloader.download(self->m_camId,
                                                       date.addDays(-1));
      });
}

QtPromise::QPromise<std::optional<PanoramaUpdater::PendingImage>>
PanoramaUpdater::downloadLatestImage(const DayImageData& dayImageData)
{
  using Result = std::optional<PendingImage>;

  if (dayImageData.images.empty())
  {
    qCWarning(lcPanomax) << "no image available for cam" << m_camId;
    emit errorOccurred(Error::NoImageAvailable);
    return QtPromise::QPromise<Result>::resolve(Result{});
  }

  const auto latestImage =
      std::ranges::max_element(dayImageData.images, {}, &ImageData::time);
  const QDateTime latestDateTime{dayImageData.date, latestImage->time};

  if (m_latestImageDateTime.isValid() &&
      latestDateTime <= m_latestImageDateTime)
  {
    qCDebug(lcPanomax) << "no new image, latest is still"
                       << m_latestImageDateTime;
    return QtPromise::QPromise<Result>::resolve(Result{});
  }

  const ImageSize* size = findImageSize(dayImageData, m_resolution);
  if (size == nullptr)
  {
    qCWarning(lcPanomax) << "resolution" << m_resolution << "not offered by cam"
                         << m_camId << "- falling back to"
                         << m_fallbackResolution;
    size = findImageSize(dayImageData, m_fallbackResolution);
  }
  if (size == nullptr)
  {
    qCWarning(lcPanomax) << "fallback resolution" << m_fallbackResolution
                         << "not offered by cam" << m_camId;
    emit errorOccurred(Error::ResolutionNotAvailable);
    return QtPromise::QPromise<Result>::resolve(Result{});
  }

  qCDebug(lcPanomax) << "downloading image" << latestDateTime << "at resolution"
                     << QString::fromStdString(size->resolution);
  return m_imageDownloader.download(m_camId, latestDateTime, *size)
      .then([latestDateTime](const ImageTiles& imageTiles)
            { return Result{PendingImage{latestDateTime, imageTiles}}; });
}

} // namespace wsgui::core::panomax
