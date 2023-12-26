#pragma once

#include <QDateTime>
#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "panomaximage.h"
#include "panomaximagesinfo.h"

namespace wsgui {
namespace panomax {

class PanomaxRecentImage : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString camId READ camId WRITE setCamId NOTIFY camIdChanged FINAL)
  Q_PROPERTY(std::vector<wsgui::panomax::PanomaxImageSize::Resolution> resolutions READ resolutions WRITE setResolutions
                 NOTIFY resolutionsChanged FINAL)
  QML_ELEMENT

public:
  explicit PanomaxRecentImage(QObject* parent = nullptr);

  QString camId() const;
  void setCamId(const QString& newCamId);

  std::vector<PanomaxImageSize::Resolution> resolutions() const;
  void setResolutions(const std::vector<PanomaxImageSize::Resolution>& newResolutions);

signals:
  void camIdChanged();
  void resolutionsChanged();

private:
  void imagesInfoUpdated();

  PanomaxImage m_image;
  PanomaxImagesInfo m_imagesInfo;
  QString m_camId;
  std::vector<PanomaxImageSize::Resolution> m_resolutions;
  QTimer m_updateTimer;
  QDateTime m_recentImageTime;
};

} // namespace panomax
} // namespace wsgui
