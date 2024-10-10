import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui
import wsgui.colors

Control {
  id: control

  property double windDirection: Number.NaN
  property double windValue: Number.NaN
  property string windUnit

  property double gustValue: Number.NaN
  property string gustUnit

  property url icon
  property int iconSize: 48

  property double backgroundOpacity: 1
  property double unitWidth: 50

  signal clicked()

  height: 170
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

    ColumnLayout {
      anchors.fill: parent
      anchors.topMargin: 6
      anchors.bottomMargin: 6
      spacing: 0

      Item {
        id: _windContainer

        Layout.fillWidth: true
        height: _windValueLabel.height

        Column {
          id: _arrowIconContainer

          anchors.verticalCenter: parent.verticalCenter
          anchors.left: parent.left
          anchors.leftMargin: 12

          width: control.iconSize

          Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: d.directionString
            font.pixelSize: 24
            font.bold: true
          }

          Image {
            id: _arrowIcon

            anchors.horizontalCenter: parent.horizontalCenter

            visible: !Number.isNaN(control.windDirection)
            transformOrigin: Item.Center
            rotation: control.windDirection

            sourceSize: Qt.size(40, 40)
            source: IconProvider.getIconSource("qrc:/icons/north.svg", control.Material.foreground)
          }
        }

        Label {
          id: _windValueLabel

          anchors.left: _arrowIconContainer.right
          anchors.right: _windDirectionLabel.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 12

          horizontalAlignment: Text.AlignRight
          fontSizeMode: Text.HorizontalFit
          font.pixelSize: 57
          font.bold: true
          text: d.formatValue(control.windValue)
        }

        Label {
          id: _windDirectionLabel

          anchors.baseline: _windValueLabel.baseline
          anchors.right: parent.right
          anchors.rightMargin: 12

          width: control.unitWidth

          horizontalAlignment: Text.AlignHCenter
          fontSizeMode: Text.HorizontalFit
          font.pixelSize: 32
          text: control.windUnit
        }
      }

      Item {
        id: _gustContainer

        Layout.fillWidth: true
        height: _gustValueLabel.height

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
            source: IconProvider.getIconSource(control.icon, control.Material.foreground)
          }
        }

        Label {
          id: _gustValueLabel

          anchors.left: _iconContainer.right
          anchors.right: _unitLabel.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 12

          horizontalAlignment: Text.AlignRight
          fontSizeMode: Text.HorizontalFit
          font.pixelSize: 57
          font.bold: true
          text: d.formatValue(control.gustValue)
        }

        Label {
          id: _unitLabel

          anchors.baseline: _gustValueLabel.baseline
          anchors.right: parent.right
          anchors.rightMargin: 12

          width: control.unitWidth

          horizontalAlignment: Text.AlignHCenter
          fontSizeMode: Text.HorizontalFit
          font.pixelSize: 32
          text: control.gustUnit
        }
      }
    }
  }

  QtObject {
    id: d

    readonly property string directionString: {
      if (Number.isNaN(control.windDirection)) {
        return ""
      }

      if (control.windDirection > 337.5 || control.windDirection <= 22.5) {
        return "N"
      }
      if (control.windDirection <= 67.5) {
        return "NO"
      }
      if (control.windDirection <= 112.5) {
        return "O"
      }
      if (control.windDirection <= 157.5) {
        return "SO"
      }
      if (control.windDirection <= 202.5) {
        return "S"
      }
      if (control.windDirection <= 247.5) {
        return "SW"
      }
      if (control.windDirection <= 247.5) {
        return "W"
      }
      if (control.windDirection <= 337.5) {
        return "NW"
      }

      return ""
    }

    function formatValue(value: double): string {
      if (Number.isNaN(value)) {
        return ""
      }
      return value.toFixed(1)
    }
  }
}
