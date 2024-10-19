#include "imagesdirectory.h"

#include <QDir>
#include <QFile>

namespace wsgui
{
namespace core
{

ImagesDirectory::ImagesDirectory(QObject* parent)
    : QObject{parent}
{
}

const QString& ImagesDirectory::directoryPath() const
{
  return m_directoryPath;
}

void ImagesDirectory::setDirectoryPath(const QString& newDirectoryPath)
{
  if (m_directoryPath == newDirectoryPath)
    return;
  m_directoryPath = newDirectoryPath;
  emit directoryPathChanged();

  loadImages();
}

const std::vector<QImage>& ImagesDirectory::images() const
{
  return m_images;
}

void ImagesDirectory::setImages(const std::vector<QImage>& newImages)
{
  if (m_images == newImages)
    return;
  m_images = newImages;
  emit imagesChanged();
}

void ImagesDirectory::loadImages()
{
  std::vector<QImage> images;

  QDir dir{m_directoryPath};

  for (const QFileInfo& fi: dir.entryInfoList(QDir::Files))
  {
    QImage image{QString{fi.absoluteFilePath()}};
    if (!image.isNull())
    {
      images.push_back(image);
    }
  }

  setImages(images);
}

} // namespace core
} // namespace wsgui
