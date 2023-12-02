#pragma once

#include <QtMessageHandler>

namespace wsgui {

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

} // namespace wsgui
