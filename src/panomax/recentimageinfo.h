#pragma once

#include <QObject>

#include "dayinfodownloader.h"

namespace wsgui
{
namespace panomax
{

class RecentImageInfo : public QObject
{
  Q_OBJECT
public:
  explicit RecentImageInfo(QObject* parent = nullptr);

  int camId() const;
  void setCamId(int camId);
  void updateDayInfo();

  QDateTime recentImageTime() const;
  const std::vector<ImageSize>& imageSizes() const;

signals:
  void dayInfoDownloadFailed();
  void recentImageInfoChanged();

private:
  void dayInfoDownloadFinished();

  DayInfoDownloader m_dayInfoDownloader;
  int m_camId = 0;
  DayInfo m_recentDayInfo;
};

} // namespace panomax
} // namespace wsgui
