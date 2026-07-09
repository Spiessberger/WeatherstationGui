#include "panoramamodel.h"

#include "logging.h"

namespace wsgui::app
{

namespace
{
PanoramaModel* s_instance = nullptr;
}

using core::panomax::PanoramaUpdater;

PanoramaModel::PanoramaModel(const core::AppSettings& settings, QObject* parent)
  : QObject(parent), m_updater(m_downloader)
{
  m_updater.setResolution(QString::fromStdString(settings.panomaxResolution));
  m_updater.setFallbackResolution(
      QString::fromStdString(settings.panomaxFallbackResolution));
  m_updater.setUpdateInterval(settings.updateInterval());

  connect(&m_updater, &PanoramaUpdater::imageTilesChanged, this,
          [this]() { emit imageTilesChanged(); });
  connect(&m_updater, &PanoramaUpdater::errorOccurred, this,
          [](PanoramaUpdater::Error error)
          { qCWarning(lcApp) << "panorama update error:" << error; });

  if (settings.panomaxCamId <= 0)
  {
    qCWarning(lcApp)
        << "no Panomax camera configured; the panorama background stays "
           "empty. Set a positive \"panomaxCamId\" in the settings file to "
           "enable it.";
    return;
  }

  m_updater.setCamId(settings.panomaxCamId);
  m_updater.start();
}

void PanoramaModel::setInstance(PanoramaModel* instance)
{
  s_instance = instance;
  QQmlEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
}

PanoramaModel* PanoramaModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
  Q_UNUSED(qmlEngine)
  Q_UNUSED(jsEngine)
  Q_ASSERT(s_instance);
  return s_instance;
}

const core::ImageTiles& PanoramaModel::imageTiles() const
{
  return m_updater.imageTiles();
}

} // namespace wsgui::app
