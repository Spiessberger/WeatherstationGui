#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "panomaximagedownloader.h"
#include "panomaximageinfo.h"
#include "panomaximageprovider.h"
#include "tiledimagemodel.h"

namespace wsgui {
namespace panomax {

class PanomaxImages : public QObject
{
    Q_OBJECT
    Q_PROPERTY(wsgui::TiledImageModel *recentImageModel READ recentImageModel CONSTANT)
    QML_ELEMENT
public:
    explicit PanomaxImages(QObject *parent = nullptr);

    static void setPanomaxImageProvider(PanomaxImageProvider *imageProvider);

    TiledImageModel *recentImageModel();

signals:

    void recentImageModelChanged();

private:
    void updateRecentImageInfo();
    void recentImageInfoReceived();
    void downloadRecentImage(PanomaxImageInfo::Resolution resolution);
    void recentImageDownloadFinished();

    static PanomaxImageProvider *m_imageProvider;

    QString m_camId;
    QTimer m_recentUpdateTimer;
    QNetworkAccessManager m_netManager;
    QNetworkReply *m_recentReply = nullptr;
    QNetworkReply *m_recentImageDefaultReply = nullptr;
    PanomaxImageInfo m_recentImageInfo;

    struct ImageDownload
    {
        PanomaxImageInfo::Resolution resolution = PanomaxImageInfo::Invalid;
        QDateTime imageTime;
        std::unique_ptr<PanomaxImageDownloader> imageDownloader;
    };
    ImageDownload m_recentImageDownload;
    TiledImageModel m_recentImageModel;
};

} // namespace panomax
} // namespace wsgui
