#include "recentimageinfo.h"

#include <QLoggingCategory>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::panomax::RecentImageInfo")
}

namespace wsgui
{
namespace panomax
{

RecentImageInfo::RecentImageInfo()
{
  connect(&m_dayInfoDownloader,
          &DayInfoDownloader::finished,
          this,
          &RecentImageInfo::dayInfoDownloadFinished);
  connect(&m_dayInfoDownloader,
          &DayInfoDownloader::failed,
          this,
          &RecentImageInfo::dayInfoDownloadFailed);
}

int RecentImageInfo::camId() const
{
  return m_camId;
}

void RecentImageInfo::setCamId(int camId)
{
  m_camId = camId;
}

void RecentImageInfo::updateDayInfo()
{
  if (m_dayInfoDownloader.downloading())
  {
    m_dayInfoDownloader.abort();
  }
  m_dayInfoDownloader.download(m_camId);
}

QDateTime RecentImageInfo::recentImageTime() const
{
  if (m_recentDayInfo.date.isNull() || m_recentDayInfo.imageTimes.empty())
  {
    return {};
  }
  return QDateTime{m_recentDayInfo.date, m_recentDayInfo.imageTimes.back()};
}

const std::vector<ImageSize>& RecentImageInfo::imageSizes() const
{
  return m_recentDayInfo.imageSizes;
}

void RecentImageInfo::dayInfoDownloadFinished()
{
  const DayInfo& dayInfo = m_dayInfoDownloader.dayInfo();

  if (dayInfo.imageTimes.empty())
  {
    qCWarning(log) << "no image times";
    return;
  }

  if (dayInfo.imageSizes.empty())
  {
    qCWarning(log) << "no image sizes";
    return;
  }

  const QDateTime imageTime{dayInfo.date, dayInfo.imageTimes.back()};

  if (imageTime < recentImageTime())
  {
    return;
  }

  if (imageTime == recentImageTime() && dayInfo.imageSizes == m_recentDayInfo.imageSizes)
  {
    return;
  }

  m_recentDayInfo = dayInfo;
  emit recentImageInfoChanged();
}

} // namespace panomax
} // namespace wsgui
