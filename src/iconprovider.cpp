#include "iconprovider.h"

#include <QImageReader>
#include <QLoggingCategory>
#include <QPainter>
#include <QQmlFile>
#include <QUrlQuery>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::IconProvider")
}

namespace wsgui
{

IconProvider::IconProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QUrl IconProviderHelper::getIconSource(const QUrl& iconPath, const QColor& color)
{
  QUrl ret{QString{"image://%1/%2"}.arg(ImageProviderId, iconPath.toString())};

  QUrlQuery colorQuery;
  colorQuery.addQueryItem("color", color.name(QColor::HexRgb));
  ret.setQuery(colorQuery);

  return ret;
}

IconProviderHelper::Icon IconProviderHelper::getIconFromIdentifier(const QString& id)
{
  QUrl url{id};
  QUrlQuery query{url};

  Icon icon;
  icon.iconPath = url.toString(QUrl::RemoveQuery);
  icon.color = query.queryItemValue("color");

  return icon;
}

QImage IconProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
  const IconProviderHelper::Icon icon = IconProviderHelper::getIconFromIdentifier(id);

  QImageReader imageReader{QQmlFile::urlToLocalFileOrQrc(icon.iconPath)};

  if (requestedSize.isValid() && !requestedSize.isNull())
  {
    imageReader.setScaledSize(requestedSize);
  }

  QImage image = imageReader.read();

  if (image.isNull())
  {
    qCWarning(log) << imageReader.errorString();
    return {};
  }

  *size = imageReader.size();

  QPainter painter{&image};

  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(image.rect(), icon.color);

  return image;
}

} // namespace wsgui
