#include "panomaximagesinfo.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

namespace wsgui {
namespace panomax {

// %1 = camId
// %2 = images info date in format yyyy-MM-dd or emtpy for current date
static const QString urlTemplate = QStringLiteral("https://api.panomax.com/1.0/cams/%1/images/day/%2");

PanomaxImagesInfo::PanomaxImagesInfo(QObject* parent) : QObject(parent)
{
}

const std::vector<PanomaxImageSize>& PanomaxImagesInfo::imageSizes() const
{
  return m_imageSizes;
}

std::vector<QDateTime> PanomaxImagesInfo::imageTimes() const
{
  return m_imageTimes;
}

QString PanomaxImagesInfo::camId() const
{
  return m_camId;
}

void PanomaxImagesInfo::setCamId(const QString& newCamId)
{
  m_camId = newCamId;
}

QDate PanomaxImagesInfo::imagesDate() const
{
  return m_imagesDate;
}

void PanomaxImagesInfo::setImagesDate(const QDate& newImagesDate)
{
  m_imagesDate = newImagesDate;
}

void PanomaxImagesInfo::update()
{
  m_failCounter = 0;

  if (m_camId.isEmpty())
  {
    return;
  }

  if (!m_currentDownload.isNull())
  {
    qDebug() << "aborting running images info download";
    disconnect(m_currentDownload, &QNetworkReply::finished, this, &PanomaxImagesInfo::downloadFinished);
    m_currentDownload->abort();
  }

  QString url = urlTemplate.arg(m_camId).arg(m_imagesDate.isNull() ? m_imagesDate.toString("yyyy-MM-dd") : "");
  QNetworkRequest req{url};
  qDebug() << "starting download of" << url;
  m_currentDownload = m_netManager.get(req);

  connect(m_currentDownload, &QNetworkReply::finished, m_currentDownload, &QNetworkReply::deleteLater);
  connect(m_currentDownload, &QNetworkReply::finished, this, &PanomaxImagesInfo::downloadFinished);
}

void PanomaxImagesInfo::downloadFinished()
{
  if (m_currentDownload.isNull())
  {
    qWarning() << "download reply is null";
    return;
  }

  if (m_currentDownload->error() != QNetworkReply::NoError)
  {
    m_failCounter++;
    qWarning() << "images info download failed:" << m_currentDownload->errorString();
    qWarning() << "fail counter:" << m_failCounter;
  }
  else
  {
    m_failCounter = 0;
    parseImagesInfo(m_currentDownload->readAll());
  }
}

void PanomaxImagesInfo::parseImagesInfo(const QByteArray& data)
{

  QJsonObject infoJson = QJsonDocument::fromJson(data).object();

  if (infoJson.isEmpty())
  {
    qWarning() << "invalid image info json";
    emit updateFailed();
    return;
  }
  if (!infoJson.contains("date"))
  {
    qWarning() << "image info does not contain date";
    emit updateFailed();
    return;
  }
  if (!infoJson.contains("sizes"))
  {
    qWarning() << "image info does not contain sizes array";
    emit updateFailed();
    return;
  }
  if (!infoJson.contains("images"))
  {
    qWarning() << "image info does not contain images";
    emit updateFailed();
    return;
  }

  QDate date = QDate::fromString(infoJson["date"].toString(), Qt::ISODate);
  if (!date.isValid())
  {
    qWarning() << "image info contains invalid date" << date;
    emit updateFailed();
    return;
  }

  m_imageSizes.clear();
  m_imageTimes.clear();

  for (const QJsonValue& size : infoJson["sizes"].toArray())
  {
    QJsonObject sizeObj = size.toObject();

    PanomaxImageSize imageSize;

    QString resolution = sizeObj["resolution"].toString();
    imageSize.setResolution(PanomaxImageSize::stringToResolution(resolution));
    imageSize.setNumTiles(sizeObj["cols"].toInt(0));

    if (imageSize.numTiles() > 0 && imageSize.resolution() != PanomaxImageSize::Resolution::None)
    {
      m_imageSizes.push_back(imageSize);
    }
  }

  for (const QJsonValue& image : infoJson["images"].toArray())
  {
    QJsonObject imageObj = image.toObject();

    if (image["available"].toBool(false))
    {
      QTime time = QTime::fromString(image["time"].toString(), Qt::ISODate);
      if (time.isValid())
      {
        m_imageTimes.push_back(QDateTime{date, time});
      }
    }
  }

  emit updated();
}

} // namespace panomax
} // namespace wsgui
