import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui

Control {
  id: control

  property double value: Number.NaN
  property string unit

  property url icon
  property int iconSize: 48

  property double backgroundOpacity: 1
  property double unitWidth: 50

  signal clicked()

  height: 100
  width: 250

  Material.roundedScale: Material.LargeScale
  Material.background: Theme.primaryContainer
  Material.foreground: Theme.onPrimaryContainer

  background: Item {
    Rectangle {
      id: _background

      anchors.fill: parent

      opacity: control.backgroundOpacity
      radius: control.Material.roundedScale
      color: control.Material.background
    }

    Rectangle {
      id: _stateLayer

      anchors.fill: parent

      visible: _mouseArea.pressed
      opacity: 0.1
      radius: _background.radius
      color: control.Material.foreground
    }

    MouseArea {
      id: _mouseArea
      anchors.fill: parent
      onClicked: control.clicked()
    }
  }

  contentItem: Item {
    Item {
      id: _iconContainer

      anchors.verticalCenter: parent.verticalCenter
      anchors.left: parent.left
      anchors.leftMargin: 12

      height: control.iconSize
      width: control.iconSize

      Image {
        id: _icon

        anchors.centerIn: parent
        sourceSize: Qt.size(control.iconSize, control.iconSize)
        source: control.icon ? IconProvider.getIconSource(control.icon, control.Material.foreground) : ""
      }
    }

    Label {
      id: _valueLabel

      anchors.left: _iconContainer.right
      anchors.right: _unitLabel.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 12

      horizontalAlignment: Text.AlignRight
      fontSizeMode: Text.HorizontalFit
      font.pixelSize: 57
      font.bold: true
      text: d.formatValue(control.value)
    }

    Label {
      id: _unitLabel

      anchors.baseline: _valueLabel.baseline
      anchors.right: parent.right
      anchors.rightMargin: 12

      width: control.unitWidth

      horizontalAlignment: Text.AlignHCenter
      fontSizeMode: Text.HorizontalFit
      font.pixelSize: 32
      text: control.unit
    }
  }

  QtObject {
    id: d

    function formatValue(value: double): string {
      if (Number.isNaN(value)) {
        return ""
      }
      return value.toFixed(1)
    }
  }
}
