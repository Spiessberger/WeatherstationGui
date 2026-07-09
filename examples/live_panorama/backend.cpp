#include "backend.h"

#include <QDebug>

using namespace std::chrono_literals;
using wsgui::core::panomax::PanoramaUpdater;

Backend::Backend(QObject* parent) : QObject(parent), m_updater(m_downloader)
{
  m_updater.setUpdateInterval(30s);

  connect(&m_updater, &PanoramaUpdater::imageTilesChanged, this,
          [this]() { emit imageTilesChanged(); });
  connect(&m_updater, &PanoramaUpdater::errorOccurred, this,
          [](PanoramaUpdater::Error error)
          { qWarning() << "panorama update error:" << error; });
}

int Backend::camId() const
{
  return m_updater.camId();
}

void Backend::setCamId(int camId)
{
  if (camId == m_updater.camId())
  {
    return;
  }
  m_updater.setCamId(camId);
  emit camIdChanged();
}

const QString& Backend::resolution() const
{
  return m_updater.resolution();
}

void Backend::setResolution(const QString& resolution)
{
  if (resolution == m_updater.resolution())
  {
    return;
  }
  m_updater.setResolution(resolution);
  emit resolutionChanged();
}

const QString& Backend::fallbackResolution() const
{
  return m_updater.fallbackResolution();
}

void Backend::setFallbackResolution(const QString& fallbackResolution)
{
  if (fallbackResolution == m_updater.fallbackResolution())
  {
    return;
  }
  m_updater.setFallbackResolution(fallbackResolution);
  emit fallbackResolutionChanged();
}

const wsgui::core::ImageTiles& Backend::imageTiles() const
{
  return m_updater.imageTiles();
}

void Backend::classBegin()
{
}

// start polling only after all properties have been set
void Backend::componentComplete()
{
  m_updater.start();
}
