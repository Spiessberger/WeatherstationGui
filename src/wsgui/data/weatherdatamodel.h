#pragma once

#include <QAbstractTableModel>
#include <QQmlEngine>

#include <data/weatherdatadao.h>

namespace wsgui
{
namespace data
{

class WeatherDataModel : public QAbstractTableModel
{
  Q_OBJECT
  Q_PROPERTY(QDateTime from READ from WRITE setFrom NOTIFY fromChanged FINAL)
  Q_PROPERTY(QDateTime to READ to WRITE setTo NOTIFY toChanged FINAL)
  QML_ELEMENT
public:
  static void setDataAccessObject(WeatherDataDAO* weatherDataDAO);

  enum Columns
  {
    Timestamp = 0,
    Temperature,
    Humidity,
    WindSpeed,
    WindGust,
    WindDirection,
    Rain
  };
  Q_ENUM(Columns)

  explicit WeatherDataModel(QObject* parent = nullptr);

  QDateTime from() const;
  void setFrom(const QDateTime& newFrom);

  QDateTime to() const;
  void setTo(const QDateTime& newTo);

  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

signals:
  void fromChanged();
  void toChanged();

private:
  static WeatherDataDAO* s_weatherDataDAO;

  void updateWeatherData();

  QDateTime m_from;
  QDateTime m_to;

  std::vector<WeatherData> m_weatherData;
};

} // namespace data
} // namespace wsgui
