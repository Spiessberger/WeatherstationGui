#include "panomaxrecentimage.h"

#include <chrono>

using namespace std::chrono_literals;

namespace wsgui {
namespace panomax {

PanomaxRecentImage::PanomaxRecentImage(QObject* parent) : QObject{parent}
{
  connect(&m_imagesInfo, &PanomaxImagesInfo::updated, this, &PanomaxRecentImage::imagesInfoUpdated);
  connect(&m_updateTimer, &QTimer::timeout, &m_imagesInfo, &PanomaxImagesInfo::update);

  m_updateTimer.setInterval(1min);
  m_imagesInfo.update();
}

QString PanomaxRecentImage::camId() const
{
  return m_imagesInfo.camId();
}

void PanomaxRecentImage::setCamId(const QString& newCamId)
{
  if (m_camId == newCamId)
  {
    return;
  }
  m_camId = newCamId;
  emit camIdChanged();

  m_image.setCamId(m_camId);
  m_imagesInfo.setCamId(m_camId);

  m_imagesInfo.update();
  m_updateTimer.start();
}

std::vector<wsgui::panomax::PanomaxImageSize::Resolution> PanomaxRecentImage::resolutions() const
{
  return m_resolutions;
}

void PanomaxRecentImage::setResolutions(const std::vector<wsgui::panomax::PanomaxImageSize::Resolution>& newResolutions)
{
  if (m_resolutions == newResolutions)
  {
    return;
  }
  m_resolutions = newResolutions;
  emit resolutionsChanged();
}

void PanomaxRecentImage::imagesInfoUpdated()
{
  bool updateImages = false;
  std::vector<PanomaxImageSize> imageSizes;

  for (PanomaxImageSize::Resolution resolution : m_resolutions)
  {
    auto iter =
        std::find_if(m_imagesInfo.imageSizes().cbegin(),
                     m_imagesInfo.imageSizes().cend(),
                     [resolution](const PanomaxImageSize& imageSize) { return imageSize.resolution() == resolution; });
    if (iter == m_imagesInfo.imageSizes().cend())
    {
      qWarning() << "resolution" << resolution << "not available";
    }
    else
    {
      imageSizes.push_back(*iter);
    }
  }
  if (imageSizes != m_image.requestedImageSizes())
  {
    m_image.setRequestedImageSizes(imageSizes);
    updateImages = true;
  }
  if (!m_imagesInfo.imageTimes().empty() && m_imagesInfo.imageTimes().back() > m_recentImageTime)
  {
    m_recentImageTime = m_imagesInfo.imageTimes().back();
    m_image.setImageTime(m_recentImageTime);
    updateImages = true;
  }

  if (updateImages)
  {
    m_image.updateImages();
  }
}

} // namespace panomax
} // namespace wsgui
