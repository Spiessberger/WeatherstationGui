#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include <chrono>
#include <queue>
#include <vector>

#include "imagedownloader.h"
#include "recentimageinfo.h"

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
  Q_PROPERTY(wsgui::panomax::ImageResolution thumbResolution READ thumbResolution WRITE
                 setThumbResolution NOTIFY thumbResolutionChanged FINAL)
  Q_PROPERTY(std::vector<wsgui::panomax::ImageResolution> imageResolutions READ imageResolutions
                 WRITE setImageResolutions NOTIFY imageResolutionsChanged FINAL)
  Q_PROPERTY(
      std::vector<QImage> thumbImageTiles READ thumbImageTiles NOTIFY thumbImageTilesChanged FINAL)
  Q_PROPERTY(std::vector<QImage> imageTiles READ imageTiles NOTIFY imageTilesChanged FINAL)
  Q_PROPERTY(int progress READ progress NOTIFY progressChanged FINAL)
  QML_ELEMENT
public:
  BackgroundImage();

  int camId() const;
  void setCamId(int newCamId);

  std::vector<ImageResolution> imageResolutions() const;
  void setImageResolutions(const std::vector<ImageResolution>& newImageResolutions);

  const std::vector<QImage>& thumbImageTiles() const;
  const std::vector<QImage>& imageTiles() const;

  int progress() const;

  int updateIntervalMs() const;
  void setUpdateIntervalMs(int newUpdateIntervalMs);

  wsgui::panomax::ImageResolution thumbResolution() const;
  void setThumbResolution(const wsgui::panomax::ImageResolution& newThumbResolution);

signals:
  void camIdChanged();
  void updateIntervalChanged();
  void thumbResolutionChanged();
  void imageResolutionsChanged();
  void thumbImageTilesChanged();
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
  void restartImageTilesDownload();
  void updateResolutionQueue();
  void imageDownloadFinished();
  void downloadImageTiles();

  int m_camId = 0;
  std::chrono::milliseconds m_updateInterval = std::chrono::minutes{1};
  wsgui::panomax::ImageResolution m_thumbResolution = ImageResolution::None;
  std::vector<ImageResolution> m_imageResolutions;
  std::vector<QImage> m_thumbImageTiles;
  std::vector<QImage> m_imageTiles;

  QTimer m_dayInfoUpdateTimer;
  ImageDownloader m_imageDownloader;
  RecentImageInfo m_recentImageInfo;
  std::queue<ImageResolution> m_imageResolutionQueue;
  ImageInfo m_downloadInfo;
  ImageInfo m_tilesInfo;
};

} // namespace panomax
} // namespace wsgui
