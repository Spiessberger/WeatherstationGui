import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui

Control {
  id: root

  signal openSettings()
  signal openWeatherData()

  Material.roundedScale: Material.LargeScale
  Material.background: Theme.primary
  Material.foreground: Theme.onPrimary

  DigitalClock {
    anchors.left: parent.left
    anchors.margins: 12
    anchors.top: parent.top

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
      icon: "qrc:/icons/thermometer.svg"
      unitWidth: 40
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    ValueControl {
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
      icon: "qrc:/icons/thermometer.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
      onClicked: root.openWeatherData()
    }

    ValueControl {
      icon: "qrc:/icons/humidity_percentage.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    WindControl {
      icon: "qrc:/icons/air.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }

    ValueControl {
      icon: "qrc:/icons/rainy.svg"
      backgroundOpacity: Settings.homeScreenControlOpacity
    }
  }
}
