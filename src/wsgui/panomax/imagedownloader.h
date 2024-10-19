#pragma once

#include <QImage>

#include <vector>

#include "imagesize.h"
#include <core/downloader.h>

namespace wsgui
{
namespace panomax
{

class ImageDownloader : public core::Downloader
{
  Q_OBJECT
public:
  explicit ImageDownloader(QObject* parent = nullptr);

  bool download(int camId, const ImageSize& imageSize, const QDateTime& imageTime);

  const std::vector<QImage>& imageTiles() const;

private:
  DownloadState downloadDone(const QByteArray& data) override;
  void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) override;
  bool downloadNextTile();

  size_t m_tilesToDownload = 0;
  QString m_urlTemplate;
  std::vector<QImage> m_imageTiles;
};

} // namespace panomax
} // namespace wsgui
