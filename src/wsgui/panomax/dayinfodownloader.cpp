#include "dayinfodownloader.h"

#include <QLoggingCategory>

#include <nlohmann/json.hpp>

#include "adlserializerqstring.h"
#include "imageresolution.h"
#include "jsonserializeimageresolution.h"

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::panomax::DayInfoDownloader")
const QString dateFormat = QStringLiteral("yyyy-MM-dd");
const QString timeFormat = QStringLiteral("hh:mm:ss");
} // namespace

namespace wsgui
{
namespace panomax
{

bool DayInfoDownloader::download(int camId, const QDate& date)
{
  // %1 = camId
  // %2 = images info date in format yyyy-MM-dd or emtpy for current date
  static const QString urlTemplate =
      QStringLiteral("https://api.panomax.com/1.0/cams/%1/images/day/%2");

  const QUrl url = urlTemplate.arg(camId).arg(date.isNull() ? date.toString(dateFormat) : "");
  return startDownload(url);
}

const DayInfo& DayInfoDownloader::dayInfo() const
{
  return m_dayInfo;
}

core::Downloader::DownloadState DayInfoDownloader::downloadDone(const QByteArray& data)
{
  m_dayInfo = DayInfo{};

  nlohmann::json json;
  try
  {
    json = nlohmann::json::parse(data.constData());
  }
  catch (const nlohmann::json::exception& e)
  {
    qCWarning(log) << "failed to parse downloaded data:" << e.what();
    return DownloadState::Failed;
  }

  try
  {
    m_dayInfo.date = QDate::fromString(json.at("date").get<QString>(), dateFormat);

    const nlohmann::json sizes = json.at("sizes");
    for (const nlohmann::json& size: sizes)
    {
      ImageSize imageSize;

      imageSize.columns = size.at("cols").get<int>();
      imageSize.resolution = size.at("resolution").get<ImageResolution>();

      m_dayInfo.imageSizes.push_back(imageSize);
    }

    const nlohmann::json images = json.at("images");
    for (const nlohmann::json& image: images)
    {
      if (!image.at("available").get<bool>())
      {
        continue;
      }

      const QString timeString = image.at("time").get<QString>();
      QTime time = QTime::fromString(timeString, timeFormat);
      if (time.isValid() && !time.isNull())
      {
        m_dayInfo.imageTimes.push_back(time);
      }
      else
      {
        qCWarning(log) << "cannot time:" << timeString;
      }
    }
  }
  catch (const nlohmann::json::exception& e)
  {
    qCWarning(log) << e.what();
    m_dayInfo = DayInfo{};
    return DownloadState::Failed;
  }

  return DownloadState::Finished;
}

} // namespace panomax
} // namespace wsgui
