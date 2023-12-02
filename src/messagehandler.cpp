#include "messagehandler.h"

#include <QDateTime>
#include <QString>

#include <iostream>

namespace wsgui {

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  char loggingLevel;
  FILE* output = nullptr;

  switch (type)
  {
  case QtMsgType::QtDebugMsg:
    loggingLevel = 'D';
    break;
  case QtMsgType::QtInfoMsg:
    loggingLevel = 'I';
    break;
  case QtMsgType::QtWarningMsg:
    loggingLevel = 'W';
    break;
  case QtMsgType::QtCriticalMsg:
    loggingLevel = 'C';
    break;
  case QtMsgType::QtFatalMsg:
    loggingLevel = 'F';
    break;
  default:
    loggingLevel = '-';
  }

  switch (type)
  {
  case QtMsgType::QtDebugMsg:
  case QtMsgType::QtInfoMsg:
    output = stdout;
    break;
  default:
    output = stderr;
    break;
  }

#ifdef QT_DEBUG
  QString logMsg = QString("%1 [%2] %3 [%4] %5:%6")
                       .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
                       .arg(loggingLevel)
                       .arg(msg)
                       .arg(context.function)
                       .arg(context.file)
                       .arg(context.line);
#else
  QString logMsg =
      QString("%1 [%2] %3").arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs)).arg(loggingLevel).arg(msg);
#endif

  fprintf(output, "%s\n", qPrintable(logMsg));
  fflush(output);
}

} // namespace wsgui
