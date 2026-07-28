import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui.quick
import app.weatherstation

ApplicationWindow {
  id: root

  width: 1280
  height: 800
  visible: true

  title: qsTr("Weatherstation")

  Material.theme: Material.Dark
  Material.accent: Material.Teal

  PanoramaView {
    anchors.fill: parent

    imageTiles: Panorama.imageTiles
    autoScroll: true
  }

  Pane {
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.margins: 24

    Material.elevation: 6

    background: Rectangle {
      radius: 12
      color: Material.dialogColor
      opacity: 0.55
    }

    ColumnLayout {
      spacing: 4

      Label {
        Layout.alignment: Qt.AlignHCenter
        text: Clock.timeText
        font.pixelSize: 56
        font.weight: Font.Light
      }

      Label {
        Layout.alignment: Qt.AlignHCenter
        text: Clock.dateText
        font.pixelSize: 20
      }
    }
  }
}
