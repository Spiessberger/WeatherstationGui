#pragma once

#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>

namespace wsgui
{
namespace core
{

class NavigationItem : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString textId READ textId WRITE setTextId NOTIFY textIdChanged FINAL)
  Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
  Q_PROPERTY(QQmlComponent* contentComponent READ contentComponent WRITE setContentComponent NOTIFY
                 contentComponentChanged FINAL)
  QML_ELEMENT

public:
  NavigationItem() = default;

  QString textId() const;
  void setTextId(const QString& newTextId);

  QString icon() const;
  void setIcon(const QString& newIcon);

  QQmlComponent* contentComponent() const;
  void setContentComponent(QQmlComponent* newContentComponent);

signals:
  void textIdChanged();
  void iconChanged();
  void contentComponentChanged();

private:
  QString m_textId;
  QString m_icon;
  QQmlComponent* m_contentComponent = nullptr;
};

} // namespace core
} // namespace wsgui
