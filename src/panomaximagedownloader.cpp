#include "panomaximagedownloader.h"

namespace wsgui {
namespace panomax {

PanomaxImageDownloader::PanomaxImageDownloader(const QDateTime &imageTime,
                                               const QString &resolution,
                                               int numTiles)
    : m_numTiles{numTiles}
{
    // TODO: Use QSettings to get the cam ID
    m_camId = qEnvironmentVariable("PANOMAX_CAM_ID");

    if (m_camId.isEmpty()) {
        qWarning() << "PANOMAX_CAM_ID environment variable not set";
    }

    QString resolutionTemplate = resolution;
    if (numTiles > 1) {
        resolutionTemplate += "_%1_0";
    }
    m_url = QString{"https://panodata8.panomax.com/cams/%1/%2_%3.jpg"}
                .arg(m_camId)
                .arg(imageTime.toString("yyyy/MM/dd/HH-mm-ss"))
                .arg(resolutionTemplate);

    downloadTile(0);
}

QNetworkReply::NetworkError PanomaxImageDownloader::error() const
{
    return m_error;
}

void PanomaxImageDownloader::downloadTile(int tileIndex)
{
    QUrl url = m_url.arg(tileIndex);
    QNetworkRequest req{url};

    qDebug() << "starting download of" << url;

    m_imageReply = m_netManager.get(req);

    connect(m_imageReply, &QNetworkReply::finished, this, &PanomaxImageDownloader::downloadFinished);
}

void PanomaxImageDownloader::downloadFinished()
{
    if (m_imageReply == nullptr) {
        qWarning() << "no recent request reply";
        return;
    }

    m_imageReply->deleteLater();
    if (m_imageReply->error() != QNetworkReply::NoError) {
        qWarning() << "image download failed:" << m_imageReply->errorString();
        m_error = m_imageReply->error();
        m_imageTiles.clear();
        emit finished();
        return;
    }

    QImage image = QImage::fromData(m_imageReply->readAll());

    if (image.isNull()) {
        qWarning() << "failed to load tile" << m_imageTiles.size() << "from data";
        m_error = QNetworkReply::UnknownContentError;
        m_imageTiles.clear();
        emit finished();
        return;
    }

    m_imageTiles.push_back(image);

    if (m_imageTiles.size() == m_numTiles) {
        emit finished();
    } else {
        downloadTile(m_imageTiles.size());
    }
}

const std::vector<QImage> &PanomaxImageDownloader::imageTiles() const
{
    return m_imageTiles;
}

} // namespace panomax
} // namespace wsgui
