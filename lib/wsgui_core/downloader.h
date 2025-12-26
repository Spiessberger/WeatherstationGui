#pragma once

#include <QNetworkAccessManager>
#include <QtPromise>

namespace wsgui::core
{

class Downloader
{
public:
  explicit Downloader() = default;

  // can fail with QNetworkReply::NetworkError or QList<QSslError>
  QtPromise::QPromise<QByteArray> startDownload(const QUrl& url);
  QtPromise::QPromise<QByteArray>
  startDownload(const QUrl& url, std::chrono::milliseconds timeout);

private:
  QNetworkAccessManager m_net;
};

} // namespace wsgui::core
