#pragma once

#include <QDateTime>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPointer>

#include <queue>
#include <vector>

#include "panomaximagesize.h"

namespace wsgui {
namespace panomax {

class PanomaxImage : public QObject
{
  Q_OBJECT
public:
  explicit PanomaxImage(QObject* parent = nullptr);

  QString camId() const;
  void setCamId(const QString& newCamId);

  QDateTime imageTime() const;
  void setImageTime(const QDateTime& newImageTime);

  std::vector<PanomaxImageSize> requestedImageSizes() const;
  void setRequestedImageSizes(const std::vector<PanomaxImageSize>& newRequestedImageSizes);

  bool isAvailable(PanomaxImageSize::Resolution resolution) const;
  std::vector<PanomaxImageSize::Resolution> availableResolutions() const;

  std::vector<QImage> image(PanomaxImageSize::Resolution resolution) const;

  void updateImages();

private:
  struct Image
  {
    PanomaxImageSize::Resolution resolution = PanomaxImageSize::None;
    std::vector<QImage> tiles;
  };
  struct ImageDownload
  {
    QPointer<QNetworkReply> reply = nullptr;
    PanomaxImageSize imageSize;
    std::vector<QByteArray> tilesData;
    int failCounter = 0;
  };

  void downloadFinished();
  void downloadNextImage();
  void downloadNextTile();

  QString m_camId;
  QDateTime m_imageTime;
  std::vector<PanomaxImageSize> m_requestedImageSizes;
  std::queue<PanomaxImageSize> m_downloadQueue;
  std::vector<Image> m_images;
  ImageDownload m_currentDownload;
  QNetworkAccessManager m_netManager;
};

} // namespace panomax
} // namespace wsgui
