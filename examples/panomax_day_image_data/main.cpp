#include <QCoreApplication>
#include <QDebug>
#include <QNetworkReply>

#include <panomax/dayimagedata.h>
#include <panomax/dayimagedatadownloader.h>

using namespace wsgui::core;
using namespace wsgui::core::panomax;

void dumpData(const DayImageData& data)
{
  qDebug() << "Cam Id:" << data.camId;
  qDebug() << "Date:" << data.date;
  {
    auto debug = qDebug();
    debug << "Sizes:";
    for (const ImageSize& size : data.sizes)
    {
      debug << size.resolution;
    }
  }
  qDebug() << "Number of images:" << data.images.size() << Qt::endl;
}

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  Downloader downloader;
  DayImageDataDownloader dayImageDataDownloader{downloader};

  QVector<QtPromise::QPromise<void>> promises;
  const int camId = 10040;

  promises << dayImageDataDownloader.getDayImageData(camId)
                  .then(dumpData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  QDate date = QDate{2025, 11, 28};
  promises << dayImageDataDownloader.getDayImageData(camId, date)
                  .then(dumpData)
                  .fail([date](QNetworkReply::NetworkError error)
                        { qWarning() << date << "download error:" << error; })
                  .fail([date](const QList<QSslError>& errors)
                        { qWarning() << date << "ssl errors:" << errors; })
                  .fail([date]() { qWarning() << date << "unhandled error"; });

  promises
      << dayImageDataDownloader.getDayImageData(-1, date)
             .then(dumpData)
             .fail([date](QNetworkReply::NetworkError error)
                   { qWarning() << "invalid cam id download error:" << error; })
             .fail([date](const QList<QSslError>& errors)
                   { qWarning() << "invalid cam id ssl errors:" << errors; })
             .fail([date]()
                   { qWarning() << "invalid cam id unhandled error"; });

  date = QDate{3025, 11, 28};
  promises << dayImageDataDownloader.getDayImageData(camId, date)
                  .then(dumpData)
                  .fail([date](QNetworkReply::NetworkError error)
                        { qWarning() << date << "download error:" << error; })
                  .fail([date](const QList<QSslError>& errors)
                        { qWarning() << date << "ssl errors:" << errors; })
                  .fail([date]() { qWarning() << date << "unhandled error"; });

  QtPromise::all(promises).then([&app]() { app.quit(); });

  return app.exec();
}
