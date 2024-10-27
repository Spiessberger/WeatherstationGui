#pragma once

#include <QDate>

#include "dayinfo.h"
#include <core/downloader.h>

namespace wsgui
{
namespace panomax
{

class DayInfoDownloader : public core::Downloader
{
  Q_OBJECT
public:
  DayInfoDownloader() = default;

  bool download(int camId, const QDate& date = {});

  const DayInfo& dayInfo() const;

private:
  DownloadState downloadDone(const QByteArray& data) override;
  DayInfo m_dayInfo;
};

} // namespace panomax
} // namespace wsgui
