#include "downloader.h"

#include <QNetworkReply>

namespace wsgui::core
{

QtPromise::QPromise<QByteArray> Downloader::startDownload(const QUrl& url)
{
  return startDownload(url, std::chrono::milliseconds::zero());
}

QtPromise::QPromise<QByteArray>
Downloader::startDownload(const QUrl& url, std::chrono::milliseconds timeout)
{
  return QtPromise::QPromise<QByteArray>{
      [this, url, timeout](const auto& resolve, const auto& reject)
      {
        qDebug() << "starting download" << url;
        QNetworkRequest request{url};
        if (timeout > timeout.zero())
        {
          request.setTransferTimeout(timeout);
        }
        QNetworkReply* reply = m_net.get(request);

        QObject::connect(reply, &QNetworkReply::errorOccurred,
                         [=](QNetworkReply::NetworkError error)
                         {
                           qWarning()
                               << "error occured for download" << url << error;
                           reject(error);
                           reply->deleteLater();
                         });
        QObject::connect(reply, &QNetworkReply::sslErrors,
                         [=](const QList<QSslError>& errors)
                         {
                           qWarning()
                               << "ssl error occured for download" << url;
                           reject(errors);
                           reply->deleteLater();
                         });

        QObject::connect(reply, &QNetworkReply::finished,
                         [=]()
                         {
                           if (reply->error() == QNetworkReply::NoError)
                           {
                             qDebug() << "finished download" << url;
                             resolve(reply->readAll());
                           }
                           else
                           {
                             qWarning() << "error occured for download" << url
                                        << reply->error();
                             reject(reply->error());
                           }

                           reply->deleteLater();
                         });
      }};
}

} // namespace wsgui::core
