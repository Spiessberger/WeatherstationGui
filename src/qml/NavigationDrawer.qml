import QtQuick
import QtQuick.Controls

import wsgui

Control {
  id: root

  property list<NavigationItem> navigationItems

  property int currentIndex: 0
  readonly property Component currentContentComponent: {
    if (root.currentIndex >= 0 && root.currentIndex < root.navigationItems.length) {
      return root.navigationItems[root.currentIndex].contentComponent
    }
    return null
  }

  property color backgroundColor: Theme.surface
  property color activeTextColor: Theme.onSecondaryContainer
  property color inactiveTextColor: Theme.onSurfaceVariant
  property color activeIconColor: Theme.onSecondaryContainer
  property color inactiveIconColor: Theme.onSurfaceVariant
  property color activeIndicatorColor: Theme.secondaryContainer

  signal backClicked()

  topPadding: topInset + 12
  bottomPadding: bottomInset + 12
  leftPadding: leftInset + 12
  rightPadding: rightInset + 12

  background: Rectangle {
    radius: 16
    color: root.backgroundColor
  }

  contentItem: Item {

    Rectangle {
      id: _backButton

      anchors.left: parent.left
      anchors.top: parent.top

      width: 56
      height: 56
      radius: height / 2

      color: Theme.primaryContainer

      Image {
        anchors.centerIn: parent
        sourceSize: Qt.size(24, 24)
        source: "qrc:/icons/arrow_back.svg"
      }

      MouseArea {
        anchors.fill: parent
        onClicked: root.backClicked()
      }
    }

    Rectangle {
      id: _divider

      anchors.top: _backButton.bottom
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.topMargin: 4
      anchors.leftMargin: 16
      anchors.rightMargin: 16

      height: 1

      color: Theme.outlineVariant
    }

    Flickable {
      id: _flick

      anchors.right: parent.right
      anchors.left: parent.left
      anchors.bottom: parent.bottom
      anchors.top: _divider.bottom
      anchors.topMargin: 4

      clip: true

      Column {
        id: _listItems

        Repeater {
          model: root.navigationItems

          Item {
            id: _listItem

            required property NavigationItem modelData
            required property int index

            readonly property bool active: index === root.currentIndex

            height: 56
            width: _flick.width

            Rectangle {
              id: _highlight

              anchors.fill: parent
              visible: _listItem.active
              radius: height / 2
              color: root.activeIndicatorColor
            }

            Item {
              id: _iconContainer

              anchors.left: parent.left
              anchors.leftMargin: 16
              anchors.verticalCenter: parent.verticalCenter

              width: 24
              height: 24

              Image {
                anchors.centerIn: parent
                sourceSize: Qt.size(24, 24)
                source: _listItem.modelData.icon
              }
            }

            Text {
              anchors.verticalCenter: parent.verticalCenter
              anchors.left: _iconContainer.right
              anchors.leftMargin: 12

              color: _listItem.active ? root.activeTextColor : root.inactiveTextColor
              text: _listItem.modelData.textId
            }

            MouseArea {
              anchors.fill: parent
              onClicked: root.currentIndex = _listItem.index
            }
          }
        }
      }
    }
  }
}
