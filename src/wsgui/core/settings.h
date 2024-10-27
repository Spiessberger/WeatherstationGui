#pragma once

#include <QObject>
#include <QQmlEngine>

#include <nlohmann/json.hpp>

namespace wsgui
{
namespace core
{

class Settings : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(int backgroundCamId READ backgroundCamId WRITE setBackgroundCamId NOTIFY
                 backgroundCamIdChanged FINAL)
  Q_PROPERTY(
      bool isDarkScheme READ isDarkScheme WRITE setIsDarkScheme NOTIFY isDarkSchemeChanged FINAL)
  Q_PROPERTY(double schemeContrastLevel READ schemeContrastLevel WRITE setSchemeContrastLevel NOTIFY
                 schemeContrastLevelChanged FINAL)
  Q_PROPERTY(double homeScreenControlOpacity READ homeScreenControlOpacity WRITE
                 setHomeScreenControlOpacity NOTIFY homeScreenControlOpacityChanged FINAL)
public:
  Settings();

  int backgroundCamId() const;
  void setBackgroundCamId(int newBackgroundCamId);

  bool isDarkScheme() const;
  void setIsDarkScheme(bool newIsDarkScheme);

  double schemeContrastLevel() const;
  void setSchemeContrastLevel(double newSchemeContrastLevel);

  Q_INVOKABLE void save();
  Q_INVOKABLE void read();

  double homeScreenControlOpacity() const;
  void setHomeScreenControlOpacity(double newHomeScreenControlOpacity);

signals:
  void backgroundCamIdChanged();
  void isDarkSchemeChanged();
  void schemeContrastLevelChanged();
  void homeScreenControlOpacityChanged();

private:
  QString m_settingsFileName;
  int m_backgroundCamId = 0;
  bool m_isDarkScheme = false;
  double m_schemeContrastLevel = 0.0;
  double m_homeScreenControlOpacity = 0.2;
};

void to_json(nlohmann::json& j, const Settings& settings);

} // namespace core
} // namespace wsgui
