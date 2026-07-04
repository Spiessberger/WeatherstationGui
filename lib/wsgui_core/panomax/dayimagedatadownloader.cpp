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
namespace
{
const QString ApiUrlTemplate =
    QStringLiteral("https://api.panomax.com/1.0/cams/%1/images/day/%2");
const QString ApiDateTemplate = QStringLiteral("yyyy-MM-dd");
} // namespace

DayImageDataDownloader::DayImageDataDownloader(Downloader& downloader)
  : m_downloader(downloader)
{
}

QtPromise::QPromise<DayImageData> DayImageDataDownloader::download(int camId)
{
  return downloadAndParse(camId, ApiUrlTemplate.arg(camId).arg(""));
}

QtPromise::QPromise<DayImageData>
DayImageDataDownloader::download(int camId, const QDate& date)
{
  return downloadAndParse(
      camId, ApiUrlTemplate.arg(camId).arg(date.toString(ApiDateTemplate)));
}

// https://api.panomax.com/1.0/cams/10040/images/day
QtPromise::QPromise<DayImageData>
DayImageDataDownloader::downloadAndParse(int camId, const QUrl& url)
{
  return m_downloader.download(url).then(
      [camId](const QByteArray& data)
      {
        DayImageData dayData;
        auto error = glz::read<glz::opts{.error_on_unknown_keys = false}>(
            dayData, data.constData());
        if (error)
        {
          qWarning() << "failed to parse day image data:"
                     << QString::fromStdString(
                            glz::format_error(error, data.constData()));
          throw Error::ParsingFailed;
        }
        dayData.camId = camId;
        return dayData;
      });
}

} // namespace wsgui::core::panomax
