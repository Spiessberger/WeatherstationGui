#include "panomaximages.h"

#include <QNetworkReply>

using namespace std::chrono_literals;

namespace wsgui {
namespace panomax {

PanomaxImageProvider *PanomaxImages::m_imageProvider = nullptr;

PanomaxImages::PanomaxImages(QObject *parent)
    : QObject{parent}, m_recentImageModel{"image://" +
                                          PanomaxImageProvider::providerId +
                                          "/"} {
  Q_ASSERT(m_imageProvider != nullptr);

  // TODO: Use QSettings to get the cam ID
  m_camId = qEnvironmentVariable("PANOMAX_CAM_ID");

  if (m_camId.isEmpty()) {
    qWarning() << "PANOMAX_CAM_ID environment variable not set";
  }

  connect(&m_recentUpdateTimer, &QTimer::timeout, this,
          &PanomaxImages::updateRecentImageInfo);
  m_recentUpdateTimer.setInterval(1min);
  updateRecentImageInfo();
  m_recentUpdateTimer.start();
}

void PanomaxImages::setPanomaxImageProvider(
    PanomaxImageProvider *imageProvider) {
  Q_ASSERT(m_imageProvider == nullptr);
  m_imageProvider = imageProvider;
}

TiledImageModel *PanomaxImages::recentImageModel() {
  return &m_recentImageModel;
}

void PanomaxImages::updateRecentImageInfo() {
  if (m_recentReply != nullptr) {
    m_recentReply->abort();
  }

  QNetworkRequest req{
      QString{"https://api.panomax.com/1.0/cams/%1/images/day"}.arg(m_camId)};
  m_recentReply = m_netManager.get(req);

  connect(m_recentReply, &QNetworkReply::finished, this,
          &PanomaxImages::recentImageInfoReceived);
}

void PanomaxImages::recentImageInfoReceived() {
  if (m_recentReply == nullptr) {
    qWarning() << "no recent request reply";
    return;
  }

  m_recentReply->deleteLater();
  if (m_recentReply->error() != QNetworkReply::NoError) {
    qWarning() << "image info download failed:" << m_recentReply->errorString();
    m_recentReply = nullptr;
    return;
  }

  if (m_recentImageInfo.loadImageInfo(m_recentReply->readAll())) {
    downloadRecentImage(PanomaxImageInfo::Default);
  }
  m_recentReply = nullptr;
}

void PanomaxImages::downloadRecentImage(
    PanomaxImageInfo::Resolution resolution) {
  if (m_recentImageDownload.imageDownloader != nullptr) {
    qWarning() << "previous download still running";
  }

  QString resolutionString = PanomaxImageInfo::resolutionString(resolution);

  if (resolutionString.isEmpty()) {
    qWarning() << "no resolution string for" << resolution;
    return;
  }

  auto iter = std::ranges::find_if(
      m_recentImageInfo.imageSizes(),
      [resolution](const PanomaxImageInfo::ImageSize &imageSize) {
        return imageSize.resolution == resolution;
      });

  if (iter == m_recentImageInfo.imageSizes().end()) {
    qWarning() << "no image size" << resolution;
    return;
  }

  m_recentImageDownload.imageTime = m_recentImageInfo.recentImage();
  m_recentImageDownload.resolution = resolution;
  m_recentImageDownload.imageDownloader =
      std::make_unique<PanomaxImageDownloader>(
          m_recentImageInfo.recentImage(), resolutionString, iter->numTiles);

  connect(m_recentImageDownload.imageDownloader.get(),
          &PanomaxImageDownloader::finished, this,
          &PanomaxImages::recentImageDownloadFinished);
}

void PanomaxImages::recentImageDownloadFinished() {
  if (m_recentImageDownload.imageDownloader == nullptr) {
    qWarning() << "no recent image download";
    return;
  }

  if (m_recentImageDownload.imageDownloader->error() !=
      QNetworkReply::NoError) {
    qWarning() << "recent image download failed";
    return;
  }

  m_imageProvider->setRecentImageTile(
      m_recentImageDownload.imageDownloader->imageTiles());
  m_recentImageModel.updateTiles(
      m_recentImageDownload.imageDownloader->imageTiles(),
      m_recentImageDownload.imageTime,
      PanomaxImageInfo::resolutionString(m_recentImageDownload.resolution));

  if (m_recentImageDownload.resolution == PanomaxImageInfo::Default) {
    downloadRecentImage(PanomaxImageInfo::Full);
  } else {
    m_recentImageDownload.imageDownloader = nullptr;
    m_recentImageDownload.imageTime = {};
    m_recentImageDownload.resolution = PanomaxImageInfo::Invalid;
  }
}

} // namespace panomax
} // namespace wsgui
