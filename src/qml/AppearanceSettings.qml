import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui

Item {
  id: root

  width: 500

  Column {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: 48

    spacing: 48

    Column {
      spacing: 6

      Label {
        text: "Theme"
      }

      Pane {
        Material.background: Theme.surfaceContainerLow
        Material.foreground: Theme.onSurface
        Material.roundedScale: Material.LargeScale
        Material.accent: Theme.primary

        Column {
          spacing: 12

          Row {
            spacing: 12

            Button {
              Material.roundedScale: Material.MediumScale

              highlighted: !Settings.isDarkScheme
              display: Button.TextUnderIcon
              icon.source: "qrc:/icons/light_mode.svg"
              text: "Light"

              onClicked: Settings.isDarkScheme = false
            }
            Button {
              Material.roundedScale: Material.MediumScale

              highlighted: Settings.isDarkScheme
              display: Button.TextUnderIcon
              icon.source: "qrc:/icons/dark_mode.svg"
              text: "Dark"

              onClicked: Settings.isDarkScheme = true
            }
          }

          Column {
            Label {
              text: "Kontrast"
            }

            Slider {
              from: 0
              to: 1
              stepSize: 0.01

              value: Settings.schemeContrastLevel
              onMoved: Settings.schemeContrastLevel = value
            }
          }
        }
      }
    }
  }
}
