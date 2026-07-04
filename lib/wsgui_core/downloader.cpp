#include "downloader.h"

#include <QNetworkReply>

namespace wsgui::core
{

QtPromise::QPromise<QByteArray> Downloader::download(const QUrl& url)
{
  return download(url, std::chrono::milliseconds::zero());
}

QtPromise::QPromise<QByteArray>
Downloader::download(const QUrl& url, std::chrono::milliseconds timeout)
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
        QNetworkReply* reply = m_networkAccessManager.get(request);

        // log-only: a reply with ssl errors also emits finished, which
        // rejects with QNetworkReply::SslHandshakeFailedError; this
        // handler preserves the certificate details in the log
        QObject::connect(
            reply, &QNetworkReply::sslErrors,
            [url](const QList<QSslError>& errors)
            { qWarning() << "ssl errors for download" << url << errors; });

        QObject::connect(reply, &QNetworkReply::finished,
                         [resolve, reject, reply, url]()
                         {
                           if (reply->error() == QNetworkReply::NoError)
                           {
                             qDebug() << "finished download" << url;
                             resolve(reply->readAll());
                           }
                           else
                           {
                             qWarning() << "error occurred for download" << url
                                        << reply->error();
                             reject(reply->error());
                           }

                           reply->deleteLater();
                         });
      }};
}

} // namespace wsgui::core
