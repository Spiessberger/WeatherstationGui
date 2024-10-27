#pragma once

#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QObject>
#include <QPointer>

namespace wsgui
{
namespace core
{

class Downloader : public QObject
{
  Q_OBJECT
public:
  Downloader() = default;

  bool downloading() const;

  int retries() const;
  void setRetries(int newRetries);

  int progress() const;

  void abort();

signals:
  void failed();
  void finished();
  void progressChanged();

protected:
  enum class DownloadState
  {
    Continue,
    Finished,
    Failed
  };

  /**
   * @brief Is called after a download started with startDownload() is finished.
   * @param data The downloaded data.
   * @return true if all downloads are done and the finished signal should be emitted.
   */
  virtual DownloadState downloadDone(const QByteArray& data) = 0;

  /**
   * @brief Is called when the progress of the current download changes.
   *        Can be overloaded to set custom progress handling.
   * @param bytesReceived Bytes received for the current download.
   * @param bytesTotal Total bytes to be received for the current download.
   */
  virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
  bool startDownload(const QUrl& url);
  void setProgress(int newProgress);

private:
  void downloadFinished();
  bool startDownload(const QUrl& url, bool resetRetries);

  int m_retries = 0;
  int m_retryCounter = 0;
  int m_progress = 0;
  QUrl m_currentUrl;
  QPointer<QNetworkReply> m_currentDownload;
  QNetworkAccessManager m_netManager;
  QElapsedTimer m_downloadTimer;
};

} // namespace core
} // namespace wsgui
