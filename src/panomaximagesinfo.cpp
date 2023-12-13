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
  m_imageSizes.clear();
  m_imageTimes.clear();
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
    qDebug() << m_currentDownload->readAll();
  }
}

// bool PanomaxImagesInfo::parseImageInfo(const QByteArray& infoData)
// {
//   QJsonObject infoJson = QJsonDocument::fromJson(infoData).object();

//   if (!infoJson.contains("date"))
//   {
//     qWarning() << "image info does not contain date";
//     return false;
//   }
//   if (!infoJson.contains("sizes"))
//   {
//     qWarning() << "image info does not contain sizes";
//     return false;
//   }
//   if (!infoJson.contains("images"))
//   {
//     qWarning() << "image info does not contain images";
//     return false;
//   }
//   if (!infoJson.contains("imageAvailableCount"))
//   {
//     qWarning() << "image info does not contain imageAvailableCount";
//     return false;
//   }

//   int imageAvailableCount = infoJson["imageAvailableCount"].toInt(0);

//   if (imageAvailableCount <= 0)
//   {
//     qDebug() << "image info contains no available images";
//     return false;
//   }

//   QDate date = QDate::fromString(infoJson["date"].toString(), Qt::ISODate);
//   if (!date.isValid())
//   {
//     qWarning() << "image info contains invalid date";
//     return false;
//   }

//   if (date != m_recentImage.date())
//   {
//     m_imageSizes.clear();

//     for (const QJsonValue& size : infoJson["sizes"].toArray())
//     {
//       QJsonObject sizeObj = size.toObject();

//       ImageSize imageSize;
//       QString resolution = sizeObj["resolution"].toString();

//       if (resolution == "full")
//       {
//         imageSize.resolution = Resolution::Full;
//       }
//       else if (resolution == "default")
//       {
//         imageSize.resolution = Resolution::Default;
//       }

//       imageSize.numTiles = sizeObj["cols"].toInt(0);

//       if (imageSize.numTiles > 0 && imageSize.resolution != Resolution::Invalid)
//       {
//         m_imageSizes.push_back(imageSize);
//       }
//     }
//   }

//   QJsonArray images = infoJson["images"].toArray();

//   for (int i = images.size() - 1; i >= 0; i--)
//   {
//     QJsonObject image = images[i].toObject();

//     if (image["available"].toBool(false))
//     {
//       QTime time = QTime::fromString(image["time"].toString(), Qt::ISODate);
//       if (time.isValid())
//       {
//         QDateTime timestamp = QDateTime{date, time};
//         if (timestamp > m_recentImage)
//         {
//           m_recentImage = timestamp;
//           return true;
//         }
//         else
//         {
//           return false;
//         }
//       }
//     }
//   }

//   qWarning() << "image info contains no available images";
//   return false;
// }

} // namespace panomax
} // namespace wsgui
