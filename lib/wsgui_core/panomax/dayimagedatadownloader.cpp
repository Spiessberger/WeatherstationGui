#include "dayimagedatadownloader.h"

#include <glaze/glaze.hpp>

namespace glz
{
template <> struct from<JSON, QTime>
{
  template <auto Opts>
  static void op(QTime& time, is_context auto&& ctx, auto&& it, auto&& end)
  {
    std::string timeStr;
    parse<JSON>::op<Opts>(timeStr, ctx, it, end);
    time = QTime::fromString(QString::fromStdString(timeStr), "HH:mm:ss");
  }
};

template <> struct from<JSON, QDate>
{
  template <auto Opts>
  static void op(QDate& date, is_context auto&& ctx, auto&& it, auto&& end)
  {
    std::string dateStr;
    parse<JSON>::op<Opts>(dateStr, ctx, it, end);
    date = QDate::fromString(QString::fromStdString(dateStr), "yyyy-MM-dd");
  }
};
} // namespace glz

namespace wsgui::core::panomax
{

DayImageDataDownloader::DayImageDataDownloader(Downloader& downloader)
  : m_downloader(downloader)
{
}

QString DayImageDataDownloader::apiUrlTemplate() const
{
  return m_apiUrlTemplate;
}

void DayImageDataDownloader::setApiUrlTemplate(const QString& apiUrlTemplate)
{
  m_apiUrlTemplate = apiUrlTemplate;
}

QString DayImageDataDownloader::apiDateTemplate() const
{
  return m_apiDateTemplate;
}

void DayImageDataDownloader::setApiDateTemplate(const QString& apiDateTemplate)
{
  m_apiDateTemplate = apiDateTemplate;
}

QtPromise::QPromise<DayImageData>
DayImageDataDownloader::getDayImageData(int camId)
{
  return startDownload(camId, m_apiUrlTemplate.arg(camId).arg(""));
}

QtPromise::QPromise<DayImageData>
DayImageDataDownloader::getDayImageData(int camId, const QDate& date)
{
  return startDownload(
      camId, m_apiUrlTemplate.arg(camId).arg(date.toString(m_apiDateTemplate)));
}

QtPromise::QPromise<DayImageData>
DayImageDataDownloader::startDownload(int camId, const QUrl& url)
{
  return m_downloader.startDownload(url).then(
      [camId](const QByteArray& data)
      {
        DayImageData dayData;
        auto error = glz::read<glz::opts{.error_on_unknown_keys = false}>(
            dayData, data.constData());
        if (error)
        {
          std::string error_msg = glz::format_error(error, data.constData());
          throw error;
        }
        dayData.camId = camId;
        return dayData;
      });
}

} // namespace wsgui::core::panomax
