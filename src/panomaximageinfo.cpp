#include "panomaximageinfo.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace wsgui {
namespace panomax {

PanomaxImageInfo::PanomaxImageInfo()
{
}

QDateTime PanomaxImageInfo::recentImage() const
{
  return m_recentImage;
}

const std::vector<PanomaxImageInfo::ImageSize>& PanomaxImageInfo::imageSizes() const
{
  return m_imageSizes;
}

bool PanomaxImageInfo::loadImageInfo(const QByteArray& infoData)
{
  QJsonObject infoJson = QJsonDocument::fromJson(infoData).object();

  if (!infoJson.contains("date"))
  {
    qWarning() << "image info does not contain date";
    return false;
  }
  if (!infoJson.contains("sizes"))
  {
    qWarning() << "image info does not contain sizes";
    return false;
  }
  if (!infoJson.contains("images"))
  {
    qWarning() << "image info does not contain images";
    return false;
  }
  if (!infoJson.contains("imageAvailableCount"))
  {
    qWarning() << "image info does not contain imageAvailableCount";
    return false;
  }

  int imageAvailableCount = infoJson["imageAvailableCount"].toInt(0);

  if (imageAvailableCount <= 0)
  {
    qDebug() << "image info contains no available images";
    return false;
  }

  QDate date = QDate::fromString(infoJson["date"].toString(), Qt::ISODate);
  if (!date.isValid())
  {
    qWarning() << "image info contains invalid date";
    return false;
  }

  if (date != m_recentImage.date())
  {
    m_imageSizes.clear();

    for (const QJsonValue& size : infoJson["sizes"].toArray())
    {
      QJsonObject sizeObj = size.toObject();

      ImageSize imageSize;
      QString resolution = sizeObj["resolution"].toString();

      if (resolution == "full")
      {
        imageSize.resolution = Resolution::Full;
      }
      else if (resolution == "default")
      {
        imageSize.resolution = Resolution::Default;
      }

      imageSize.numTiles = sizeObj["cols"].toInt(0);

      if (imageSize.numTiles > 0 && imageSize.resolution != Resolution::Invalid)
      {
        m_imageSizes.push_back(imageSize);
      }
    }
  }

  QJsonArray images = infoJson["images"].toArray();

  for (int i = images.size() - 1; i >= 0; i--)
  {
    QJsonObject image = images[i].toObject();

    if (image["available"].toBool(false))
    {
      QTime time = QTime::fromString(image["time"].toString(), Qt::ISODate);
      if (time.isValid())
      {
        QDateTime timestamp = QDateTime{date, time};
        if (timestamp > m_recentImage)
        {
          m_recentImage = timestamp;
          return true;
        }
        else
        {
          return false;
        }
      }
    }
  }

  qWarning() << "image info contains no available images";
  return false;
}

QString PanomaxImageInfo::resolutionString(Resolution resolution)
{
  switch (resolution)
  {
  case Resolution::Full:
    return QStringLiteral("full");
  case Resolution::Default:
    return QStringLiteral("default");
  default:
    return QStringLiteral("");
  }
}

} // namespace panomax
} // namespace wsgui
