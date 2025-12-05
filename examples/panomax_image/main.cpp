#include <QCoreApplication>
#include <QDebug>
#include <QNetworkReply>

#include <panomax/dayimagedata.h>
#include <panomax/imagedownloader.h>

using namespace wsgui::core;
using namespace wsgui::core::panomax;

void dumpImageData(const ImageTiles& tiles)
{
  qDebug() << tiles.rowCount() << "x" << tiles.columnCount();
  qDebug() << tiles.resolution();
}

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  Downloader downloader;
  ImageDownloader imageDownloader{downloader};

  QVector<QtPromise::QPromise<void>> promises;
  const int camId = 10040;

  ImageSize smallSize;
  smallSize.resolution = "small";
  smallSize.rows = 1;
  smallSize.cols = 1;

  ImageSize defaultSize;
  defaultSize.resolution = "default";
  defaultSize.rows = 1;
  defaultSize.cols = 1;

  ImageSize hdSize;
  hdSize.resolution = "hd";
  hdSize.rows = 1;
  hdSize.cols = 4;

  ImageSize fullSize;
  fullSize.resolution = "full";
  fullSize.rows = 3;
  fullSize.cols = 17;

  ImageSize invalidSize;
  invalidSize.resolution = "invalid";
  invalidSize.rows = 1;
  invalidSize.cols = 2;

  /* Successful Downloads */
  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{2025, 12, 2}, QTime{21, 0, 0}},
                            smallSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{2025, 12, 2}, QTime{21, 0, 0}},
                            defaultSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{2025, 12, 2}, QTime{21, 0, 0}},
                            hdSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{2025, 12, 2}, QTime{21, 0, 0}},
                            fullSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  /* Invalid Downloads */
  // invalid size
  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{2025, 12, 2}, QTime{21, 0, 0}},
                            invalidSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  // invalid date
  promises << imageDownloader
                  .getImage(camId,
                            QDateTime{QDate{3025, 12, 2}, QTime{21, 0, 0}},
                            hdSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  // invalid cam id
  promises << imageDownloader
                  .getImage(-1, QDateTime{QDate{3025, 12, 2}, QTime{21, 0, 0}},
                            hdSize)
                  .then(dumpImageData)
                  .fail([](QNetworkReply::NetworkError error)
                        { qWarning() << "download error:" << error; })
                  .fail([](const QList<QSslError>& errors)
                        { qWarning() << "ssl errors:" << errors; })
                  .fail([]() { qWarning() << "unhandled error"; });

  QtPromise::all(promises).then([&app]() { app.quit(); });

  return app.exec();
}
