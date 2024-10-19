#pragma once

#include <QQuickImageProvider>

#include <wsgui_global.h>

namespace wsgui
{
namespace core
{

class WSGUI_EXPORT IconProviderHelper : public QObject
{
  Q_OBJECT
  QML_NAMED_ELEMENT(IconProvider)
  QML_SINGLETON
public:
  struct Icon
  {
    QUrl iconPath;
    QColor color;
  };

  inline static const QString ImageProviderId = "icon";

  IconProviderHelper() = default;

  Q_INVOKABLE static QUrl getIconSource(const QUrl& iconPath, const QColor& color);
  static Icon getIconFromIdentifier(const QString& id);
};

class WSGUI_EXPORT IconProvider : public QQuickImageProvider
{
public:
  IconProvider();

  QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};

} // namespace core
} // namespace wsgui
