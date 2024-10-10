import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import wsgui.colors
import wsgui

Item {
  id: root

  Rectangle {
    id: _settingsContentBackground

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    width: {
      let contentWidth = 0
      if (_settingsContent.item && _settingsContent.item.width > 0) {
        contentWidth = _settingsContent.item.width + _contentArea.anchors.rightMargin
      }
      return _settingsList.width + contentWidth
    }

    Behavior on width {
      NumberAnimation {
        duration: 200
        easing.type: Easing.InOutQuad
      }
    }

    color: Theme.surfaceContainerLow
    topRightRadius: Material.LargeScale
    bottomRightRadius: Material.LargeScale

    opacity: 0.5

    // swallow click events
    MouseArea{ anchors.fill: parent }
  }

  Rectangle {
    id: _settingsColumnBackground

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    width: _settingsList.width

    color: Theme.surfaceContainerHighest
    topRightRadius: Material.LargeScale
    bottomRightRadius: Material.LargeScale

    opacity: 0.5
  }

  Item {
    id: _contentArea

    anchors.left: _settingsColumnBackground.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: _settingsContentBackground.right
    anchors.rightMargin: Math.max(_settingsContentBackground.topRightRadius, _settingsContentBackground.bottomLeftRadius)

    clip: true

    Loader {
      id: _settingsContent

      anchors.left: parent.left
      anchors.top: parent.top
      anchors.bottom: parent.bottom

      sourceComponent: d.settingsListEntries[d.selectedListIndex]?.component || undefined
    }
  }

  Column {
    id: _settingsList

    anchors.left: parent.left
    anchors.top: parent.top

    RoundButton {
      icon.source: "qrc:/icons/arrow_back.svg"
      onClicked: root.StackView.view.pop()
    }

    MenuSeparator {
      width: parent.width
    }

    Repeater {
      model:  d.settingsListEntries

      ItemDelegate {
        id: _delegate

        required property int index
        required property SettingsListEntry modelData

        Material.foreground: Theme.onSurface

        width: Math.max(parent.width, implicitWidth)

        highlighted: _delegate.index === d.selectedListIndex
        text: _delegate.modelData.text
        icon.source: _delegate.modelData.icon

        onClicked: d.selectedListIndex = _delegate.index
      }
    }
  }

  Component {
    id: _placeholderComponent

    Item {
      width: 400

      Label {
        anchors.centerIn: parent
        text: d.settingsListEntries[d.selectedListIndex].text
      }
    }
  }

  component SettingsListEntry : QtObject {
    property string text
    property string icon
    property Component component
  }

  QtObject {
    id: d

    property int selectedListIndex: 0

    readonly property list<SettingsListEntry> settingsListEntries: [
      SettingsListEntry {
        text: "Erscheinungsbild"
        icon: "qrc:/icons/palette.svg"
        component: AppearanceSettings {}
      },
      SettingsListEntry {
        text: "Netzwerk"
        icon: "qrc:/icons/wifi.svg"
        component: _placeholderComponent
      },
      SettingsListEntry {
        text: "Fehlerbehebung"
        icon: "qrc:/icons/troubleshoot.svg"
        component: _placeholderComponent
      }
    ]
  }
}
