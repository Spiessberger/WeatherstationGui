#include "downloader.h"

#include <QNetworkReply>

namespace wsgui::core
{

QtPromise::QPromise<QByteArray> Downloader::startDownload(const QUrl& url)
{
  return QtPromise::QPromise<QByteArray>{
      [this, url](const auto& resolve, const auto& reject)
      {
        const QNetworkRequest request{url};
        QNetworkReply* reply = m_net.get(request);

        QObject::connect(reply, &QNetworkReply::errorOccurred,
                         [=](QNetworkReply::NetworkError error)
                         {
                           reject(error);
                           reply->deleteLater();
                         });
        QObject::connect(reply, &QNetworkReply::sslErrors,
                         [=](const QList<QSslError>& errors)
                         {
                           reject(errors);
                           reply->deleteLater();
                         });

        QObject::connect(reply, &QNetworkReply::finished,
                         [=]()
                         {
                           if (reply->error() == QNetworkReply::NoError)
                           {
                             resolve(reply->readAll());
                           }
                           else
                           {
                             reject(reply->error());
                           }

                           reply->deleteLater();
                         });
      }};
}

} // namespace wsgui::core
