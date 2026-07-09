#pragma once

#include <QLoggingCategory>

// logging category of the application shell; follows the same style as the
// library categories (wsgui.<area>) but lives in the app, not a library
namespace wsgui::app
{

Q_DECLARE_LOGGING_CATEGORY(lcApp)

} // namespace wsgui::app
