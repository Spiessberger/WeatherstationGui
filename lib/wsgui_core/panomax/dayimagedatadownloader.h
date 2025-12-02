#pragma once

#include <QFuture>
#include <QNetworkAccessManager>
#include <QObject>
#include <QPromise>

#include <downloader.h>
#include <panomax/dayimagedata.h>

namespace wsgui::core::panomax
{

class DayImageDataDownloader : public QObject
{
  Q_OBJECT
public:
  explicit DayImageDataDownloader(Downloader& downloader);

  QString apiUrlTemplate() const;
  void setApiUrlTemplate(const QString& apiUrlTemplate);

  QString apiDateTemplate() const;
  void setApiDateTemplate(const QString& apiDateTemplate);

  QtPromise::QPromise<DayImageData> getDayImageData(int camId);
  QtPromise::QPromise<DayImageData> getDayImageData(int camId,
                                                    const QDate& date);

private:
  QtPromise::QPromise<DayImageData> startDownload(int camId, const QUrl& url);

  QString m_apiUrlTemplate =
      QStringLiteral("https://api.panomax.com/1.0/cams/%1/images/day/%2");
  QString m_apiDateTemplate = QStringLiteral("yyyy-MM-dd");
  Downloader& m_downloader;
};

} // namespace wsgui::core::panomax
