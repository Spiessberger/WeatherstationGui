#pragma once

#include <QQmlEngine>

#include <wsguienums.h>

namespace wsgui::quick
{

// exposes the wsgui::core namespace and its Q_ENUM_NS enums to QML as
// "WsGui" (e.g. WsGui.Light), like Qt exposes the Qt namespace
class WsGuiForeign
{
  Q_GADGET
  QML_FOREIGN_NAMESPACE(wsgui::core)
  QML_NAMED_ELEMENT(WsGui)
};

} // namespace wsgui::quick
