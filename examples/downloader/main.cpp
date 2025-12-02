#include <QCoreApplication>
#include <QDebug>
#include <QNetworkReply>

#include <downloader.h>

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  wsgui::core::Downloader downloader;

  const std::vector<QUrl> urls{
      {"https://api.panomax.com/1.0/cams/10040/images/day"},
      {"invalid_url"},
      {"http://ipv4.download.thinkbroadband.com/100MB.zip"}};

  std::vector<QtPromise::QPromise<void>> promises;

  for (const QUrl& url : urls)
  {
    auto promise =
        downloader.startDownload(url)
            .then([url](const QByteArray& data)
                  { qDebug() << url << "received" << data.size() << "bytes"; })
            .fail([url](QNetworkReply::NetworkError error)
                  { qWarning() << url << "download error:" << error; })
            .fail([url](const QList<QSslError>& errors)
                  { qWarning() << url << "ssl errors:" << errors; })
            .fail([url]() { qWarning() << url << "unhandled error"; });
    promises.push_back(promise);
  }

  QtPromise::all(promises).then([&app]() { app.quit(); });

  return app.exec();
}
