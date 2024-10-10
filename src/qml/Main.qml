import QtQuick
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
  
  HomeScreen {
    anchors.fill: parent
  }
}
