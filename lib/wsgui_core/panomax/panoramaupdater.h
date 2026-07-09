#pragma once

#include <chrono>
#include <optional>

#include <QDateTime>
#include <QTimer>

#include <downloader.h>
#include <imagetiles.h>
#include <panomax/dayimagedatadownloader.h>
#include <panomax/imagedownloader.h>

namespace wsgui::core::panomax
{

// keeps the most recent image of a camera available as ImageTiles by
// polling the day metadata on a configurable interval and downloading
// tiles only when a newer image has been published
class PanoramaUpdater : public QObject
{
  Q_OBJECT

public:
  enum class Error
  {
    DownloadFailed,        // network failure, retried on the next tick
    MetadataParsingFailed, // day metadata could not be parsed
    ImageLoadingFailed,    // tile data could not be decoded
    NoImageAvailable,      // neither current nor previous day has images
    ResolutionNotAvailable // neither resolution nor fallback offered
  };
  Q_ENUM(Error)

  explicit PanoramaUpdater(Downloader& downloader, QObject* parent = nullptr);

  int camId() const;
  void setCamId(int camId);

  const QString& resolution() const;
  void setResolution(const QString& resolution);

  const QString& fallbackResolution() const;
  void setFallbackResolution(const QString& fallbackResolution);

  std::chrono::milliseconds updateInterval() const;
  void setUpdateInterval(std::chrono::milliseconds updateInterval);

  bool isRunning() const;
  void start();
  void stop();

  const ImageTiles& imageTiles() const;

signals:
  void imageTilesChanged(const wsgui::core::ImageTiles& imageTiles);
  void errorOccurred(Error error);

private:
  struct PendingImage
  {
    QDateTime dateTime;
    ImageTiles imageTiles;
  };

  void checkForNewImage();
  void restartIfRunning();
  QtPromise::QPromise<DayImageData> downloadDayImageData();
  QtPromise::QPromise<std::optional<PendingImage>>
  downloadLatestImage(const DayImageData& dayImageData);

  DayImageDataDownloader m_dayImageDataDownloader;
  ImageDownloader m_imageDownloader;
  QTimer m_timer;

  int m_camId = 0;
  QString m_resolution = QStringLiteral("default");
  QString m_fallbackResolution = QStringLiteral("default");

  ImageTiles m_imageTiles;
  QDateTime m_latestImageDateTime;
  bool m_running = false;
  bool m_updateInFlight = false;
  // incremented whenever in-flight results must be discarded (stop or
  // reconfiguration); promise continuations compare against it
  int m_runId = 0;
};

} // namespace wsgui::core::panomax
