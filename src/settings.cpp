#include "settings.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLoggingCategory>

using json = nlohmann::json;

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::Settings")
}

namespace wsgui
{

namespace keys
{
namespace
{
const char* const backgroundCamId = "backgroundCamId";
const char* const isDarkScheme = "isDarkScheme";
const char* const schemeContrastLevel = "schemeContrastLevel";
const char* const homeScreenControlOpacity = "homeScreenControlOpacity";
} // namespace
} // namespace keys

Settings::Settings(QObject* parent)
    : QObject{parent}
{
  m_settingsFileName = qEnvironmentVariable("WSGUI_SETTINGS_FILE");
  if (m_settingsFileName.isEmpty())
  {
    m_settingsFileName = "wsgui_settings.json";
  }
  QFileInfo fi{m_settingsFileName};

  if (fi.exists())
  {
    read();
  }
  else
  {
    if (!fi.dir().exists())
    {
      if (!fi.dir().mkpath("."))
      {
        qCWarning(log) << "failed to create directory for settings file";
        return;
      }
    }
    save();
  }
}

int Settings::backgroundCamId() const
{
  return m_backgroundCamId;
}

void Settings::setBackgroundCamId(int newBackgroundCamId)
{
  if (m_backgroundCamId == newBackgroundCamId)
  {
    return;
  }
  m_backgroundCamId = newBackgroundCamId;
  emit backgroundCamIdChanged();
}

bool Settings::isDarkScheme() const
{
  return m_isDarkScheme;
}

void Settings::setIsDarkScheme(bool newIsDarkScheme)
{
  if (m_isDarkScheme == newIsDarkScheme)
  {
    return;
  }
  m_isDarkScheme = newIsDarkScheme;
  emit isDarkSchemeChanged();
}

double Settings::schemeContrastLevel() const
{
  return m_schemeContrastLevel;
}

void Settings::setSchemeContrastLevel(double newSchemeContrastLevel)
{
  if (qFuzzyCompare(m_schemeContrastLevel, newSchemeContrastLevel))
  {
    return;
  }
  m_schemeContrastLevel = newSchemeContrastLevel;
  emit schemeContrastLevelChanged();
}

double Settings::homeScreenControlOpacity() const
{
  return m_homeScreenControlOpacity;
}

void Settings::setHomeScreenControlOpacity(double newHomeScreenControlOpacity)
{
  if (qFuzzyCompare(m_homeScreenControlOpacity, newHomeScreenControlOpacity))
  {
    return;
  }
  m_homeScreenControlOpacity = newHomeScreenControlOpacity;
  emit homeScreenControlOpacityChanged();
}

void Settings::save()
{
  nlohmann::json j = *this;

  QFile f{m_settingsFileName};
  if (!f.open(QIODevice::WriteOnly))
  {
    qCWarning(log) << "failed to open settings file for writing:" << f.errorString();
    return;
  }
  f.write(j.dump(4).data());
}

void Settings::read()
{
  QFile f{m_settingsFileName};
  if (!f.open(QIODevice::ReadOnly))
  {
    qCWarning(log) << "failed to open settings file for reading:" << f.errorString();
    return;
  }
  nlohmann::json j = nlohmann::json::parse(f.readAll());

  if (j.contains(keys::backgroundCamId))
  {
    setBackgroundCamId(j.at(keys::backgroundCamId).get<int>());
  }
  if (j.contains(keys::isDarkScheme))
  {
    setIsDarkScheme(j.at(keys::isDarkScheme).get<bool>());
  }
  if (j.contains(keys::schemeContrastLevel))
  {
    setSchemeContrastLevel(j.at(keys::schemeContrastLevel).get<double>());
  }
  if (j.contains(keys::homeScreenControlOpacity))
  {
    setHomeScreenControlOpacity(j.at(keys::homeScreenControlOpacity).get<double>());
  }
}

void to_json(nlohmann::json& j, const Settings& settings)
{
  j = json{{keys::backgroundCamId, settings.backgroundCamId()},
           {keys::isDarkScheme, settings.isDarkScheme()},
           {keys::schemeContrastLevel, settings.schemeContrastLevel()},
           {keys::homeScreenControlOpacity, settings.homeScreenControlOpacity()}};
}

} // namespace wsgui
