#pragma once

#include <QLoggingCategory>

// logging categories of wsgui_quick, one per feature area; use with
// qCDebug()/qCWarning() instead of the category-less qDebug()/qWarning()
namespace wsgui::quick
{

Q_DECLARE_LOGGING_CATEGORY(lcImageTiles)

} // namespace wsgui::quick
