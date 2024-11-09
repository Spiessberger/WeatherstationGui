#include "navigationitem.h"

namespace wsgui
{
namespace core
{

QString NavigationItem::textId() const
{
  return m_textId;
}

void NavigationItem::setTextId(const QString& newTextId)
{
  if (m_textId == newTextId)
    return;
  m_textId = newTextId;
  emit textIdChanged();
}

QString NavigationItem::icon() const
{
  return m_icon;
}

void NavigationItem::setIcon(const QString& newIcon)
{
  if (m_icon == newIcon)
    return;
  m_icon = newIcon;
  emit iconChanged();
}

QQmlComponent* NavigationItem::contentComponent() const
{
  return m_contentComponent;
}

void NavigationItem::setContentComponent(QQmlComponent* newContentComponent)
{
  if (m_contentComponent == newContentComponent)
    return;
  m_contentComponent = newContentComponent;
  emit contentComponentChanged();
}

} // namespace core
} // namespace wsgui
