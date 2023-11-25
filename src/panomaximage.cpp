#include "panomaximage.h"

namespace wsgui {
namespace panomax {

PanomaxImage::PanomaxImage(QObject* parent) : QObject{parent}
{
}

QString PanomaxImage::camId() const
{
  return m_camId;
}

void PanomaxImage::setCamId(const QString& newCamId)
{
  m_camId = newCamId;
}

QDateTime PanomaxImage::imageTime() const
{
  return m_imageTime;
}

void PanomaxImage::setImageTime(const QDateTime& newImageTime)
{
  m_imageTime = newImageTime;
}

std::vector<PanomaxImageSize> PanomaxImage::requestedImageSizes() const
{
  return m_requestedImageSizes;
}

void PanomaxImage::setRequestedImageSizes(const std::vector<PanomaxImageSize>& newRequestedImageSizes)
{
  m_requestedImageSizes = newRequestedImageSizes;
}

bool PanomaxImage::isAvailable(PanomaxImageSize::Resolution resolution) const
{
  return std::find_if(m_images.cbegin(), m_images.cend(), [resolution](const auto& image) {
           return image.resolution == resolution;
         }) != m_images.cend();
}

std::vector<PanomaxImageSize::Resolution> PanomaxImage::availableResolutions() const
{
  std::vector<PanomaxImageSize::Resolution> ret;

  for (const auto& image : m_images)
  {
    ret.push_back(image.resolution);
  }

  return ret;
}

std::vector<QImage> PanomaxImage::image(PanomaxImageSize::Resolution resolution) const
{
  for (const auto& image : m_images)
  {
    if (image.resolution == resolution)
    {
      return image.tiles;
    }
  }
  return std::vector<QImage>{};
}

} // namespace panomax
} // namespace wsgui
