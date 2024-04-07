#pragma once

#include <QObject>
#include <QQmlEngine>

#include <nlohmann/json.hpp>

namespace wsgui
{

class Settings : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(int backgroundCamId READ backgroundCamId WRITE setBackgroundCamId NOTIFY
                 backgroundCamIdChanged FINAL)
public:
  explicit Settings(QObject* parent = nullptr);

  int backgroundCamId() const;
  void setBackgroundCamId(int newBackgroundCamId);

  Q_INVOKABLE void save();
  Q_INVOKABLE void read();

signals:
  void backgroundCamIdChanged();

private:
  QString m_settingsFileName;
  int m_backgroundCamId = 0;
};

void to_json(nlohmann::json& j, const Settings& settings);

} // namespace wsgui
