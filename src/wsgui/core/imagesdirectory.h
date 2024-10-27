#pragma once

#include <QImage>
#include <QObject>
#include <QQmlEngine>

namespace wsgui
{
namespace core
{

class ImagesDirectory : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString directoryPath READ directoryPath WRITE setDirectoryPath NOTIFY
                 directoryPathChanged FINAL)
  Q_PROPERTY(std::vector<QImage> images READ images NOTIFY imagesChanged FINAL)
  QML_ELEMENT
public:
  ImagesDirectory() = default;

  const QString& directoryPath() const;
  void setDirectoryPath(const QString& newDirectoryPath);

  const std::vector<QImage>& images() const;

signals:
  void directoryPathChanged();
  void imagesChanged();

private:
  void setImages(const std::vector<QImage>& newImages);
  void loadImages();

  QString m_directoryPath;
  std::vector<QImage> m_images;
};

} // namespace core
} // namespace wsgui
