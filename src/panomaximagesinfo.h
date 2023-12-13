#pragma once

#include <QDateTime>
#include <QNetworkAccessManager>
#include <QObject>

#include <vector>

#include "panomaximagesize.h"

namespace wsgui {
namespace panomax {

class PanomaxImagesInfo : public QObject
{
  Q_OBJECT
public:
  explicit PanomaxImagesInfo(QObject* parent = nullptr);

  QString camId() const;
  void setCamId(const QString& newCamId);

  QDate imagesDate() const;
  void setImagesDate(const QDate& newImagesDate);

  const std::vector<PanomaxImageSize>& imageSizes() const;
  std::vector<QDateTime> imageTimes() const;

  void update();

private:
  void downloadFinished();

  QString m_camId;
  QDate m_imagesDate;
  std::vector<PanomaxImageSize> m_imageSizes;
  std::vector<QDateTime> m_imageTimes;
  QNetworkAccessManager m_netManager;
  QPointer<QNetworkReply> m_currentDownload;
  int m_failCounter = 0;
};

} // namespace panomax
} // namespace wsgui
