#pragma once

#include <QDate>

#include "dayinfo.h"
#include "downloader.h"

namespace wsgui
{
namespace panomax
{

class DayInfoDownloader : public Downloader
{
  Q_OBJECT
public:
  explicit DayInfoDownloader(QObject* parent = nullptr);

  bool download(int camId, const QDate& date = {});

  const DayInfo& dayInfo() const;

private:
  DownloadState downloadDone(const QByteArray& data) override;
  DayInfo m_dayInfo;
};

} // namespace panomax
} // namespace wsgui
