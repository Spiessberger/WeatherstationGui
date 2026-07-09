import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui.quick

ApplicationWindow {
  id: root

  // set from C++ via setInitialProperties()
  property bool startFullscreen: false

  width: 1024
  height: 600
  visible: true
  visibility: root.startFullscreen ? Window.FullScreen
                                   : Window.AutomaticVisibility
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
    anchors.right: parent.right
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
