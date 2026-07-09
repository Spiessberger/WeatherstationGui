#pragma once

#include <QObject>
#include <QQmlEngine>

#include <appsettings.h>
#include <downloader.h>
#include <imagetiles.h>
#include <panomax/panoramaupdater.h>

namespace wsgui::app
{

// QML singleton "Panorama": the live panorama background tiles, fed by the
// core PanoramaUpdater configured from AppSettings in C++. One singleton per
// feature area keeps files small as more data gets exposed later (weather
// values etc. become new singletons, not new properties on a god object).
class PanoramaModel : public QObject
{
  Q_OBJECT
  QML_NAMED_ELEMENT(Panorama)
  QML_SINGLETON

  Q_PROPERTY(wsgui::core::ImageTiles imageTiles READ imageTiles NOTIFY
                 imageTilesChanged FINAL)

public:
  explicit PanoramaModel(const core::AppSettings& settings,
                         QObject* parent = nullptr);

  // the instance lives in main() and is injected before the engine loads;
  // setInstance() marks it CppOwnership so the engine never deletes it
  static void setInstance(PanoramaModel* instance);
  static PanoramaModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

  const core::ImageTiles& imageTiles() const;

signals:
  void imageTilesChanged();

private:
  core::Downloader m_downloader;
  core::panomax::PanoramaUpdater m_updater;
};

} // namespace wsgui::app
