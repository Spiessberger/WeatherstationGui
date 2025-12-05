#pragma once

#include <QNetworkAccessManager>

#include <downloader.h>
#include <panomax/dayimagedata.h>

namespace wsgui::core::panomax
{

class DayImageDataDownloader
{
public:
  explicit DayImageDataDownloader(Downloader& downloader);

  QtPromise::QPromise<DayImageData> getDayImageData(int camId);
  QtPromise::QPromise<DayImageData> getDayImageData(int camId,
                                                    const QDate& date);

private:
  QtPromise::QPromise<DayImageData> startDownload(int camId, const QUrl& url);

  Downloader& m_downloader;
};

} // namespace wsgui::core::panomax
