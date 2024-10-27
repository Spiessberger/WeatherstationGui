#include "downloader.h"

#include <QLoggingCategory>
#include <QNetworkReply>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::Downloader")
}

namespace wsgui
{
namespace core
{

bool Downloader::downloading() const
{
  return !m_currentDownload.isNull();
}

int Downloader::retries() const
{
  return m_retries;
}

void Downloader::setRetries(int newRetries)
{
  m_retries = newRetries;
}

void Downloader::abort()
{
  if (m_currentDownload)
  {
    disconnect(m_currentDownload, &QNetworkReply::finished, this, &Downloader::downloadFinished);
    m_currentDownload->abort();
    m_currentDownload = nullptr;
  }
}

int Downloader::progress() const
{
  return m_progress;
}

void Downloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  if (bytesTotal > 0)
  {
    setProgress(100 * bytesReceived / bytesTotal);
  }
  else
  {
    setProgress(0);
  }
}

bool Downloader::startDownload(const QUrl& url)
{
  return startDownload(url, true);
}

void Downloader::setProgress(int newProgress)
{
  if (m_progress == newProgress)
  {
    return;
  }
  m_progress = newProgress;
  emit progressChanged();
}

bool Downloader::startDownload(const QUrl& url, bool resetRetries)
{
  if (m_currentDownload)
  {
    qCWarning(log) << "Download already in progress";
    return false;
  }
  qCDebug(log) << "starting download of" << url;

  if (resetRetries)
  {
    m_retryCounter = 0;
  }
  m_currentUrl = url;
  m_currentDownload = m_netManager.get(QNetworkRequest{url});
  connect(m_currentDownload,
          &QNetworkReply::finished,
          m_currentDownload,
          &QNetworkReply::deleteLater);
  connect(m_currentDownload, &QNetworkReply::finished, this, &Downloader::downloadFinished);
  connect(m_currentDownload, &QNetworkReply::downloadProgress, this, &Downloader::downloadProgress);
  m_downloadTimer.start();

  return true;
}

void Downloader::downloadFinished()
{
  if (m_currentDownload->error() != QNetworkReply::NoError)
  {
    if (m_retryCounter < m_retries)
    {
      m_retryCounter++;
      qCWarning(log) << "Download of" << m_currentUrl
                     << "failed:" << m_currentDownload->errorString()
                     << "retry counter:" << m_retryCounter << "took:" << m_downloadTimer.elapsed()
                     << "ms";
      // current download needs to be reset in order to retry
      m_currentDownload = nullptr;
      startDownload(m_currentUrl, false);
    }
    else
    {
      emit failed();
    }
    return;
  }

  qCDebug(log) << "finished download of" << m_currentUrl << "after" << m_downloadTimer.elapsed()
               << "ms";
  QByteArray data = m_currentDownload->readAll();
  // current download needs to be reset in order to be able to start new one in downloadDone
  m_currentDownload = nullptr;
  DownloadState ret = downloadDone(data);
  if (ret == DownloadState::Finished)
  {
    emit finished();
  }
  else if (ret == DownloadState::Failed)
  {
    emit failed();
  }
}

} // namespace core
} // namespace wsgui
