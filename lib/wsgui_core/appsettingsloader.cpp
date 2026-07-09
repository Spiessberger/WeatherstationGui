#include "appsettingsloader.h"

#include "logging.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

#include <glaze/glaze.hpp>

namespace wsgui::core
{

QString AppSettingsLoader::defaultFilePath()
{
  return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
         QStringLiteral("/settings.json");
}

std::expected<AppSettings, AppSettingsLoader::Error>
AppSettingsLoader::load(const QString& filePath)
{
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    qCWarning(lcSettings) << "settings file not readable:" << filePath;
    return std::unexpected(Error::FileNotReadable);
  }

  const QByteArray data = file.readAll();

  AppSettings settings;
  auto error = glz::read<glz::opts{.error_on_unknown_keys = false}>(
      settings, data.constData());
  if (error)
  {
    qCWarning(lcSettings) << "failed to parse settings file:" << filePath << "-"
                          << QString::fromStdString(
                                 glz::format_error(error, data.constData()));
    return std::unexpected(Error::ParsingFailed);
  }

  return settings;
}

bool AppSettingsLoader::save(const AppSettings& settings,
                             const QString& filePath)
{
  const QFileInfo fileInfo(filePath);
  if (!QDir().mkpath(fileInfo.absolutePath()))
  {
    qCWarning(lcSettings) << "failed to create directory for settings file:"
                          << filePath;
    return false;
  }

  auto result = glz::write<glz::opts{.prettify = true}>(settings);
  if (!result)
  {
    qCWarning(lcSettings) << "failed to serialize settings:"
                          << QString::fromStdString(
                                 glz::format_error(result.error()));
    return false;
  }

  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    qCWarning(lcSettings) << "settings file not writable:" << filePath;
    return false;
  }

  file.write(QByteArray::fromStdString(*result));
  return true;
}

} // namespace wsgui::core
