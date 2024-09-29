#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include <chrono>
#include <queue>
#include <vector>

#include "dayinfodownloader.h"
#include "imagedownloader.h"

namespace wsgui
{
namespace panomax
{

class BackgroundImage : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int camId READ camId WRITE setCamId NOTIFY camIdChanged FINAL)
  Q_PROPERTY(int updateInterval READ updateIntervalMs WRITE setUpdateIntervalMs NOTIFY
                 updateIntervalChanged FINAL)
  Q_PROPERTY(std::vector<wsgui::panomax::ImageResolution> imageResolutions READ imageResolutions
                 WRITE setImageResolutions NOTIFY imageResolutionsChanged FINAL)
  Q_PROPERTY(std::vector<QImage> imageTiles READ imageTiles NOTIFY imageTilesChanged FINAL)
  Q_PROPERTY(int progress READ progress NOTIFY progressChanged FINAL)
  QML_ELEMENT
public:
  explicit BackgroundImage(QObject* parent = nullptr);

  int camId() const;
  void setCamId(int newCamId);

  std::vector<ImageResolution> imageResolutions() const;
  void setImageResolutions(const std::vector<ImageResolution>& newImageResolutions);

  const std::vector<QImage>& imageTiles() const;

  int progress() const;

  int updateIntervalMs() const;
  void setUpdateIntervalMs(int newUpdateIntervalMs);

signals:
  void camIdChanged();
  void updateIntervalChanged();
  void imageResolutionsChanged();
  void imageTilesChanged();
  void progressChanged();

  void imageDownloadFailed();
  void dayInfoDownloadFailed();

private:
  struct ImageInfo
  {
    ImageResolution resolution = ImageResolution::None;
    QDateTime time;
  };
  void updateDayInfo();
  void dayInfoDownloadFinished();
  void updateResolutionQueue();
  void imageDownloadFinished();
  void downloadImageTiles();

  int m_camId = 0;
  std::chrono::milliseconds m_updateInterval = std::chrono::minutes{1};
  QTimer m_dayInfoUpdateTimer;
  ImageDownloader m_imageDownloader;
  DayInfoDownloader m_dayInfoDownloader;
  ImageInfo m_downloadInfo;
  ImageInfo m_tilesInfo;
  std::vector<QImage> m_imageTiles;
  std::vector<ImageResolution> m_imageResolutions;
  std::queue<ImageResolution> m_imageResolutionQueue;
};

} // namespace panomax
} // namespace wsgui
