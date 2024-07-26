import QtQuick
import QtQuick.Layouts
import WeatherstationGui

Item {
  id: root

  ColumnLayout {
    Text {
      text: HomeScreenData.time
    }
    Text {
      text: HomeScreenData.date
    }

    Row {
      Text {
        text: HomeScreenData.indoorClimate.temperature.value
      }
      Text {
        text: HomeScreenData.indoorClimate.temperature.unit
      }
    }

    Row {
      Text {
        text: HomeScreenData.indoorClimate.humidity.value
      }
      Text {
        text: HomeScreenData.indoorClimate.humidity.unit
      }
    }

    Row {
      Text {
        text: HomeScreenData.weatherStation.temperature.value
      }
      Text {
        text: HomeScreenData.weatherStation.temperature.unit
      }
    }

    Row {
      Text {
        text: HomeScreenData.weatherStation.humidity.value
      }
      Text {
        text: HomeScreenData.weatherStation.humidity.unit
      }
    }
  }
}
