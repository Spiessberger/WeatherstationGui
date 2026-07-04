#pragma once

#include <QObject>

// central header for enums shared between C++ and QML, following the
// pattern of Qt's own qnamespace.h; moc requires Q_NAMESPACE and all
// Q_ENUM_NS declarations to live in the same file
namespace wsgui::core
{
Q_NAMESPACE

enum class Theme
{
  Light,
  Dark
};
Q_ENUM_NS(Theme)

} // namespace wsgui::core
