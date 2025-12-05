#pragma once

#include <downloader.h>
#include <imagetiles.h>
#include <panomax/dayimagedata.h>

namespace wsgui::core::panomax
{

// https://panodata.panomax.com/cams/10040/2025/11/28/12-50-00_small.jpg
class ImageDownloader
{
public:
  ImageDownloader(Downloader& downloader);

  QtPromise::QPromise<ImageTiles> getImage(int camId, const QDateTime& dateTime,
                                           const ImageSize& size);

private:
  void downloadDone(const QByteArray& data, size_t downloadId, int row,
                    int column);

  Downloader& m_downloader;
};

} // namespace wsgui::core::panomax
