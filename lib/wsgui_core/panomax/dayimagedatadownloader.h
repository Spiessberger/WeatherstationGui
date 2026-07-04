#pragma once

#include <QNetworkAccessManager>

#include <downloader.h>
#include <panomax/dayimagedata.h>

namespace wsgui::core::panomax
{

class DayImageDataDownloader
{
public:
  enum class Error
  {
    ParsingFailed
  };

  explicit DayImageDataDownloader(Downloader& downloader);

  QtPromise::QPromise<DayImageData> download(int camId);
  QtPromise::QPromise<DayImageData> download(int camId, const QDate& date);

private:
  QtPromise::QPromise<DayImageData> downloadAndParse(int camId,
                                                     const QUrl& url);

  Downloader& m_downloader;
};

} // namespace wsgui::core::panomax
