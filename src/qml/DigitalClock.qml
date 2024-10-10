import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui.colors


Control {
  id: control

  property string time
  property string date

  property double backgroundOpacity: 1

  implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                          implicitContentWidth + leftPadding + rightPadding)
  implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                           implicitContentHeight + topPadding + bottomPadding)

  padding: 12

  Material.roundedScale: Material.LargeScale
  Material.background: Theme.primaryContainer
  Material.foreground: Theme.onPrimaryContainer

  background: Rectangle {
    id: _background

    anchors.fill: parent

    opacity: control.backgroundOpacity
    radius: control.Material.roundedScale
    color: control.Material.background
  }

  contentItem: Column {
    Label {
      anchors.horizontalCenter: parent.horizontalCenter

      text: control.time
      font.pixelSize: 130
      font.bold: true
    }
    Label {
      anchors.horizontalCenter: parent.horizontalCenter

      text: control.date
      font.pixelSize: 52
    }
  }
}
