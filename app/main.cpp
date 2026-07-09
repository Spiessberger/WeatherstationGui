#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <appsettings.h>
#include <appsettingsloader.h>

#include "clockmodel.h"
#include "logging.h"
#include "panoramamodel.h"

using wsgui::core::AppSettings;
using wsgui::core::AppSettingsLoader;

int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);

  QCoreApplication::setOrganizationName(QStringLiteral("WeatherstationGui"));
  QCoreApplication::setApplicationName(QStringLiteral("WeatherstationGui"));

  QCommandLineParser parser;
  parser.setApplicationDescription(
      QStringLiteral("Weatherstation GUI - live panorama with a clock"));
  parser.addHelpOption();
  QCommandLineOption settingsOption(
      QStringLiteral("settings"), QStringLiteral("Path to the settings file."),
      QStringLiteral("path"), AppSettingsLoader::defaultFilePath());
  QCommandLineOption fullscreenOption(
      QStringLiteral("fullscreen"),
      QStringLiteral("Show the window fullscreen (kiosk mode)."));
  parser.addOption(settingsOption);
  parser.addOption(fullscreenOption);
  parser.process(app);

  const QString settingsPath = parser.value(settingsOption);
  const bool startFullscreen = parser.isSet(fullscreenOption);

  // first run: write the default file and continue; parse error: log and
  // continue with defaults. Neither prevents startup.
  AppSettings settings;
  const auto loaded = AppSettingsLoader::load(settingsPath);
  if (loaded)
  {
    settings = *loaded;
  }
  else if (loaded.error() == AppSettingsLoader::Error::FileNotReadable)
  {
    qCInfo(wsgui::app::lcApp)
        << "no settings file at" << settingsPath << "- writing defaults";
    if (!AppSettingsLoader::save(settings, settingsPath))
    {
      qCWarning(wsgui::app::lcApp)
          << "failed to write default settings file to" << settingsPath;
    }
  }
  else
  {
    qCWarning(wsgui::app::lcApp)
        << "using default settings after failing to load" << settingsPath;
  }

  QQuickStyle::setStyle(QStringLiteral("Material"));

  // the QML singletons are created here so they can be constructed from the
  // loaded settings; their create() functions hand these instances to the
  // engine (CppOwnership, never deleted by QML)
  wsgui::app::ClockModel clockModel;
  wsgui::app::ClockModel::setInstance(&clockModel);
  wsgui::app::PanoramaModel panoramaModel(settings);
  wsgui::app::PanoramaModel::setInstance(&panoramaModel);

  QQmlApplicationEngine engine;
  engine.setInitialProperties(
      {{QStringLiteral("startFullscreen"), startFullscreen}});

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("app.weatherstation", "Main");

  return app.exec();
}
