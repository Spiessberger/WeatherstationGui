import QtQuick
import QtQuick.Controls

import WeatherstationGui

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
  }

  Background {
    id: _background
    anchors.fill: parent

    applicationSchemeProvider: _applicationSchemeProvider
  }

  StackView {
    anchors.fill: parent

    initialItem: HomeScreen {
      id: _homeScreen

      opacity: _background.scrolling ? 1.0 : 0.0

      Behavior on opacity {
        NumberAnimation {
          easing.type: Easing.InOutQuad
          duration: 1000
        }
      }
    }
  }
}
