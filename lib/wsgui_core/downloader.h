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
  QtPromise::QPromise<QByteArray> download(const QUrl& url);
  QtPromise::QPromise<QByteArray> download(const QUrl& url,
                                           std::chrono::milliseconds timeout);

private:
  QNetworkAccessManager m_networkAccessManager;
};

} // namespace wsgui::core
