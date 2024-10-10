import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import WeatherstationGui

Control {
  id: root

  signal openSettings()

  Material.roundedScale: Material.LargeScale
  Material.background: Theme.primary
  Material.foreground: Theme.onPrimary

  DigitalClock {
    anchors.left: parent.left
    anchors.margins: 12
    anchors.top: parent.top

    time: HomeScreenData.time
    date: HomeScreenData.date

    backgroundOpacity: Settings.homeScreenControlOpacity

    MouseArea {
      anchors.fill: parent
      onPressAndHold: root.openSettings()
    }
  }

  Column {
    spacing: 12
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.leftMargin: 12

    ValueControl {
      value: HomeScreenData.indoorClimate.temperature.value
      unit: HomeScreenData.indoorClimate.temperature.unit
      icon: "qrc:/icons/thermometer.svg"
      unitWidth: 40
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    ValueControl {
      value: HomeScreenData.indoorClimate.humidity.value
      unit: HomeScreenData.indoorClimate.humidity.unit
      icon: "qrc:/icons/humidity_percentage.svg"
      unitWidth: 40
      backgroundOpacity: Settings.homeScreenControlOpacity
    }
  }

  Column {
    spacing: 12
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 12

    ValueControl {
      value: HomeScreenData.weatherStation.temperature.value
      unit: HomeScreenData.weatherStation.temperature.unit
      icon: "qrc:/icons/thermometer.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    ValueControl {
      value: HomeScreenData.weatherStation.humidity.value
      unit: HomeScreenData.weatherStation.humidity.unit
      icon: "qrc:/icons/humidity_percentage.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    WindControl {
      windDirection: HomeScreenData.weatherStation.windDirection
      windValue: HomeScreenData.weatherStation.windSpeed.value
      windUnit: HomeScreenData.weatherStation.windSpeed.unit
      gustValue: HomeScreenData.weatherStation.windGust.value
      gustUnit: HomeScreenData.weatherStation.windGust.unit
      icon: "qrc:/icons/air.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    ValueControl {
      value: HomeScreenData.weatherStation.rain.value
      unit: HomeScreenData.weatherStation.rain.unit
      icon: "qrc:/icons/rainy.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }
  }
}
