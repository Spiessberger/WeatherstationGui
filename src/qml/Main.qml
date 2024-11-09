import QtQuick
import QtQuick.Controls

import wsgui

Window {
  id: _window
  width: 1280
  height: 800
  visible: true
  title: "Weatherstation Gui"

  ColorSchemeProvider {
    id: _applicationSchemeProvider

    isDark: Settings.isDarkScheme
    contrast: Settings.schemeContrastLevel

    onColorsChanged: Theme.updateThemeColors(colorScheme)
    Component.onCompleted: loadSchemeFromColor("white")
  }

  Background {
    id: _background
    anchors.fill: parent

    applicationSchemeProvider: _applicationSchemeProvider
  }

  StackView {
    id: _stackView

    anchors.fill: parent

    initialItem: HomeScreen {
      id: _homeScreen

      opacity: _background.scrolling ? 1.0 : 0.0
      visible: opacity > 0

      Behavior on opacity {
        NumberAnimation {
          easing.type: Easing.InOutQuad
          duration: 1000
        }
      }

      onOpenSettings: _stackView.push(_settingsScreen)
      onOpenWeatherData: _stackView.push(_weatherDataScreen)
    }
  }

  Component {
    id: _settingsScreen

    SettingsScreen {}
  }

  Component {
    id: _weatherDataScreen

    WeatherDataScreen {
      onBackClicked: _stackView.pop()
    }
  }
}
