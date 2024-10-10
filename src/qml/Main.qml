import QtQuick
import QtQuick.Controls

import wsgui
import wsgui.colors

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
    }
  }

  Component {
    id: _settingsScreen

    SettingsScreen {}
  }
}
