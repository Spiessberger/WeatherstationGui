#pragma once

#include <QNetworkAccessManager>
#include <QObject>

#include <QtPromise>

namespace wsgui::core
{

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader() = default;

  // can fail with QNetworkReply::NetworkError or QList<QSslError>
  QtPromise::QPromise<QByteArray> startDownload(const QUrl& url);

private:
  QNetworkAccessManager m_net;
};

} // namespace wsgui::core
