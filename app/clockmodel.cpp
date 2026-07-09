#include "clockmodel.h"

#include <QDateTime>
#include <QLocale>
#include <QTime>

namespace wsgui::app
{

namespace
{
ClockModel* s_instance = nullptr;
}

ClockModel::ClockModel(QObject* parent) : QObject(parent)
{
  // single-shot; re-armed to the next second boundary after every tick so the
  // shown time never lags visibly and dateText is derived from the same tick
  m_clockTimer.setSingleShot(true);
  connect(&m_clockTimer, &QTimer::timeout, this,
          [this]()
          {
            updateClock();
            scheduleNextTick();
          });

  updateClock();
  scheduleNextTick();
}

void ClockModel::setInstance(ClockModel* instance)
{
  s_instance = instance;
  QQmlEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
}

ClockModel* ClockModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
  Q_UNUSED(qmlEngine)
  Q_UNUSED(jsEngine)
  Q_ASSERT(s_instance);
  return s_instance;
}

void ClockModel::scheduleNextTick()
{
  const int msPastSecond = QTime::currentTime().msec();
  m_clockTimer.start(std::chrono::milliseconds(1000 - msPastSecond));
}

void ClockModel::updateClock()
{
  const QDateTime now = QDateTime::currentDateTime();

  const QString timeText = now.toString(QStringLiteral("HH:mm:ss"));
  if (timeText != m_timeText)
  {
    m_timeText = timeText;
    emit timeTextChanged();
  }

  const QDate date = now.date();
  if (date != m_currentDate)
  {
    m_currentDate = date;
    m_dateText = QLocale::system().toString(date, QLocale::LongFormat);
    emit dateTextChanged();
  }
}

const QString& ClockModel::timeText() const
{
  return m_timeText;
}

const QString& ClockModel::dateText() const
{
  return m_dateText;
}

} // namespace wsgui::app
