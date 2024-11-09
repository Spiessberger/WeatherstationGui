import QtQuick
import QtQuick.Controls.Material

import wsgui

Item {
  id: root

  signal backClicked()

  NavigationDrawer {
    id: _navigationDrawer

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.margins: 8

    width: 360

    navigationItems: [
      NavigationItem {
        textId: "id_weather_data"
        icon: "qrc:/icons/table.svg"
        contentComponent: WeatherDataTable {}
      },
      NavigationItem {
        textId: "id_weather_graph"
        icon: "qrc:/icons/insert_chart.svg"
      },
      NavigationItem {
        textId: "id_weather_forecast"
        icon: "qrc:/icons/sunny.svg"
      },
      NavigationItem {
        textId: "id_weather_map"
        icon: "qrc:/icons/map.svg"
      }
    ]

    onBackClicked: root.backClicked()
  }

  Rectangle {
    anchors.left: _navigationDrawer.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.margins: 8

    color: _navigationDrawer.backgroundColor
    radius: 16

    Loader {
      anchors.fill: parent
      sourceComponent: _navigationDrawer.currentContentComponent || undefined
    }
  }
}
