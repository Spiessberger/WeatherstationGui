#include "weatherdatamodel.h"

#include <QLoggingCategory>

namespace
{
Q_LOGGING_CATEGORY(log, "wsgui.data.WeatherDataModel")
}

namespace wsgui
{
namespace data
{

WeatherDataDAO* WeatherDataModel::s_weatherDataDAO = nullptr;

void WeatherDataModel::setDataAccessObject(WeatherDataDAO* weatherDataDAO)
{
  Q_ASSERT(weatherDataDAO != nullptr);
  s_weatherDataDAO = weatherDataDAO;
}

WeatherDataModel::WeatherDataModel(QObject* parent)
    : QAbstractTableModel(parent)
{
  Q_ASSERT(s_weatherDataDAO != nullptr);
}

QVariant WeatherDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
  {
    return QVariant{};
  }

  switch (section)
  {
    case Columns::Timestamp:
      return "timestamp";
    case Columns::Temperature:
      return "temperature";
    case Columns::Humidity:
      return "humidity";
    case Columns::WindSpeed:
      return "wind_speed";
    case Columns::WindGust:
      return "wind_gust";
    case Columns::WindDirection:
      return "wind_direction";
    case Columns::Rain:
      return "rain";
  }

  qCWarning(log) << "invalide header section:" << section;
  return QVariant{};
}

int WeatherDataModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return m_weatherData.size();
}

int WeatherDataModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return QMetaEnum::fromType<Columns>().keyCount();
}

QVariant WeatherDataModel::data(const QModelIndex& index, int role) const
{
  if (role != Qt::DisplayRole || !index.isValid())
  {
    return QVariant{};
  }

  if (index.row() < 0 || index.row() >= rowCount())
  {
    qCWarning(log) << "invalide row index:" << index.row();
    return QVariant{};
  }

  const WeatherData& weatherData = m_weatherData[index.row()];
  switch (index.column())
  {
    case Columns::Timestamp:
      return QLocale{}.toString(weatherData.timestamp, QLocale::ShortFormat);
    case Columns::Temperature:
      return QString::number(weatherData.temperature, 'f', 1);
    case Columns::Humidity:
      return QString::number(weatherData.humidity, 'f', 1);
    case Columns::WindSpeed:
      return QString::number(weatherData.windSpeed, 'f', 1);
    case Columns::WindGust:
      return QString::number(weatherData.windGust, 'f', 1);
    case Columns::WindDirection:
      return weatherData.windDirection;
    case Columns::Rain:
      return QString::number(weatherData.rain, 'f', 1);
  }

  qCWarning(log) << "invalide column index:" << index.column();
  return QVariant{};
}

QHash<int, QByteArray> WeatherDataModel::roleNames() const
{
  return {{Qt::DisplayRole, "displayData"}};
}

QDateTime WeatherDataModel::from() const
{
  return m_from;
}

void WeatherDataModel::setFrom(const QDateTime& newFrom)
{
  if (m_from == newFrom)
    return;
  m_from = newFrom;
  emit fromChanged();

  updateWeatherData();
}

QDateTime WeatherDataModel::to() const
{
  return m_to;
}

void WeatherDataModel::setTo(const QDateTime& newTo)
{
  if (m_to == newTo)
    return;
  m_to = newTo;
  emit toChanged();

  updateWeatherData();
}

void WeatherDataModel::updateWeatherData()
{
  beginResetModel();
  m_weatherData = s_weatherDataDAO->getData(m_from, m_to);
  endResetModel();
}

} // namespace data
} // namespace wsgui
