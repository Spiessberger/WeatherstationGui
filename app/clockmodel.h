#pragma once

#include <QDate>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QTimer>

namespace wsgui::app
{

// QML singleton "Clock": time/date display strings. One singleton per
// feature area keeps files small as more data gets exposed later (weather
// values etc. become new singletons, not new properties on a god object).
class ClockModel : public QObject
{
  Q_OBJECT
  QML_NAMED_ELEMENT(Clock)
  QML_SINGLETON

  Q_PROPERTY(QString timeText READ timeText NOTIFY timeTextChanged FINAL)
  Q_PROPERTY(QString dateText READ dateText NOTIFY dateTextChanged FINAL)

public:
  explicit ClockModel(QObject* parent = nullptr);

  // the instance lives in main() and is injected before the engine loads;
  // setInstance() marks it CppOwnership so the engine never deletes it
  static void setInstance(ClockModel* instance);
  static ClockModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

  const QString& timeText() const;
  const QString& dateText() const;

signals:
  void timeTextChanged();
  void dateTextChanged();

private:
  // (re)arm the timer so it fires on the next whole-second boundary
  void scheduleNextTick();
  void updateClock();

  QTimer m_clockTimer;
  QString m_timeText;
  QString m_dateText;
  QDate m_currentDate;
};

} // namespace wsgui::app
