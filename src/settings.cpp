#include "settings.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLoggingCategory>

#include "adlserializerqstring.h"

using json = nlohmann::json;

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui::Settings")
}

namespace wsgui
{

namespace keys
{
const char* const backgroundCamId = "backgroundCamId";
}

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
}

void to_json(nlohmann::json& j, const Settings& settings)
{
  j = json{{keys::backgroundCamId, settings.backgroundCamId()}};
}

} // namespace wsgui
