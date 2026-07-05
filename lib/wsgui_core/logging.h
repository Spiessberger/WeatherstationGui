#pragma once

#include <QLoggingCategory>

// logging categories of wsgui_core, one per feature area; use with
// qCDebug()/qCWarning() instead of the category-less qDebug()/qWarning()
namespace wsgui::core
{

Q_DECLARE_LOGGING_CATEGORY(lcNetwork)
Q_DECLARE_LOGGING_CATEGORY(lcPanomax)
Q_DECLARE_LOGGING_CATEGORY(lcImageTiles)
Q_DECLARE_LOGGING_CATEGORY(lcColorScheme)

} // namespace wsgui::core
