#pragma once

#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

namespace wsgui {
namespace panomax {

class PanomaxImageDownloader : public QObject
{
    Q_OBJECT
public:
    explicit PanomaxImageDownloader(const QDateTime &imageTime,
                                    const QString &resolution,
                                    int numTiles);

    QNetworkReply::NetworkError error() const;

    const std::vector<QImage> &imageTiles() const;

signals:
    void finished();

private:
    void downloadTile(int tileIndex);
    void downloadFinished();

    QNetworkReply::NetworkError m_error = QNetworkReply::NoError;
    QString m_camId;
    QString m_url;
    int m_numTiles;
    std::vector<QImage> m_imageTiles;
    QNetworkAccessManager m_netManager;
    QNetworkReply *m_imageReply = nullptr;
};

} // namespace panomax
} // namespace wsgui

