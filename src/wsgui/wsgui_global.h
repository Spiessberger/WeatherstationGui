#pragma once

#include <QtCore/QtGlobal>

#if defined(WSGUI_LIBRARY)
#define WSGUI_EXPORT Q_DECL_EXPORT
#else
#define WSGUI_EXPORT Q_DECL_IMPORT
#endif
