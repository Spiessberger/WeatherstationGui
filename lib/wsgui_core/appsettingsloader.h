#pragma once

#include <expected>

#include <QString>

#include <appsettings.h>

namespace wsgui::core
{

class AppSettingsLoader
{
public:
  enum class Error
  {
    FileNotReadable,
    ParsingFailed
  };

  // <QStandardPaths::AppConfigLocation>/settings.json; depends on
  // QCoreApplication::applicationName()/organizationName() being set
  static QString defaultFilePath();

  static std::expected<AppSettings, Error> load(const QString& filePath);

  // pretty-printed; creates parent directories as needed
  static bool save(const AppSettings& settings, const QString& filePath);
};

} // namespace wsgui::core
