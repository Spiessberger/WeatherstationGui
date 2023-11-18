#pragma once

#include <QQuickImageProvider>
#include <QQmlEngine>

namespace wsgui {
namespace panomax {

class PanomaxImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    static const QString providerId;

    PanomaxImageProvider();

    // id: <ISO 8601 Datetime>/<resolution>/<tile>
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    void setRecentImageTile(const std::vector<QImage> &imageTiles);

private:
    std::vector<QImage> m_recentImageTiles;
};

} // namespace panomax
} // namespace wsgui

