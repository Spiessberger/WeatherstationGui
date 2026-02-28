import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Layouts

import lib.wsgui_quick

Window {
  width: 640
  height: 480
  visible: true
  title: "Color Scheme Viewer"

  ColorScheme {
    id: localColorScheme
  }

  ColorSchemeLoader {
    id: colorSchemeLoader
    colorScheme: localColorScheme
    theme: themeSwitch.checked ? ColorSchemeLoader.Dark : ColorSchemeLoader.Light
    contrast: contrastSlider.value
  }

  FileDialog {
    id: imageDialog

    currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
    onAccepted: d.imageColors = colorSchemeLoader.colorsFromImage(imageDialog.selectedFile)
  }

  ColumnLayout {
    anchors.fill: parent
    anchors.margins: 12

    RowLayout {
      Button {
        Layout.alignment: Qt.AlignLeft
        text: "load Image"
        onClicked: imageDialog.open()
      }

      Item {
        Layout.fillWidth: true
        Layout.fillHeight: true
      }

      Column {
        Label {
          anchors.horizontalCenter: parent.horizontalCenter
          text: "Contrast: " + contrastSlider.value
        }
        Slider {
          id: contrastSlider
          Layout.alignment: Qt.AlignCenter
          value: 0
          from: -1
          to: 1
          stepSize: 0.5
          snapMode: Slider.SnapAlways
        }
      }

      Item {
        Layout.fillWidth: true
        Layout.fillHeight: true
      }

      Switch {
        id: themeSwitch
        Layout.alignment: Qt.AlignRight
        text: "Dark"
      }
    }

    Label {
      visible: d.imageColors.length > 0
      text: "select source color:"
    }

    Row {
      spacing: 12

      Repeater {
        model: d.imageColors

        Rectangle {
          id: colorSelection

          required property color modelData

          width: 100
          height: 70
          radius: 10
          color: modelData
          border.color: "black"
          border.width: colorSelection.color === d.sourceColor ? 5 : 0

          MouseArea {
            anchors.fill: parent
            onClicked: {
              d.sourceColor = colorSelection.color
              colorSchemeLoader.loadSchemeFromColor(d.sourceColor)
            }
          }
        }
      }
    }

    Rectangle {
      Layout.fillWidth: true

      height: 1
      color: "black"
    }

    ScrollView {
      Layout.fillWidth: true
      Layout.fillHeight: true

      contentWidth: availableWidth

      ColumnLayout {
        width: parent.width
        spacing: 16

        // Helper component: single color role card
        component ColorRoleCard: Rectangle {
          required property color roleColor
          required property color onRoleColor
          required property string roleName

          implicitWidth: 160
          implicitHeight: 64
          radius: 8
          color: roleColor

          Text {
            anchors.centerIn: parent
            text: roleName
            color: onRoleColor
            font.pixelSize: 13
            font.weight: Font.Medium
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            width: parent.width - 8
          }
        }

        Text { text: "Primary"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "primary";          roleColor: localColorScheme.primary;          onRoleColor: localColorScheme.onPrimary }
          ColorRoleCard { roleName: "onPrimary";        roleColor: localColorScheme.onPrimary;        onRoleColor: localColorScheme.primary }
          ColorRoleCard { roleName: "primaryContainer"; roleColor: localColorScheme.primaryContainer; onRoleColor: localColorScheme.onPrimaryContainer }
          ColorRoleCard { roleName: "onPrimaryContainer"; roleColor: localColorScheme.onPrimaryContainer; onRoleColor: localColorScheme.primaryContainer }
          ColorRoleCard { roleName: "inversePrimary";   roleColor: localColorScheme.inversePrimary;   onRoleColor: localColorScheme.primary }
        }

        Text { text: "Primary Fixed"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "primaryFixed";          roleColor: localColorScheme.primaryFixed;          onRoleColor: localColorScheme.onPrimaryFixed }
          ColorRoleCard { roleName: "primaryFixedDim";       roleColor: localColorScheme.primaryFixedDim;       onRoleColor: localColorScheme.onPrimaryFixed }
          ColorRoleCard { roleName: "onPrimaryFixed";        roleColor: localColorScheme.onPrimaryFixed;        onRoleColor: localColorScheme.primaryFixed }
          ColorRoleCard { roleName: "onPrimaryFixedVariant"; roleColor: localColorScheme.onPrimaryFixedVariant; onRoleColor: localColorScheme.primaryFixed }
        }

        Text { text: "Secondary"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "secondary";            roleColor: localColorScheme.secondary;            onRoleColor: localColorScheme.onSecondary }
          ColorRoleCard { roleName: "onSecondary";          roleColor: localColorScheme.onSecondary;          onRoleColor: localColorScheme.secondary }
          ColorRoleCard { roleName: "secondaryContainer";   roleColor: localColorScheme.secondaryContainer;   onRoleColor: localColorScheme.onSecondaryContainer }
          ColorRoleCard { roleName: "onSecondaryContainer"; roleColor: localColorScheme.onSecondaryContainer; onRoleColor: localColorScheme.secondaryContainer }
        }

        Text { text: "Secondary Fixed"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "secondaryFixed";          roleColor: localColorScheme.secondaryFixed;          onRoleColor: localColorScheme.onSecondaryFixed }
          ColorRoleCard { roleName: "secondaryFixedDim";       roleColor: localColorScheme.secondaryFixedDim;       onRoleColor: localColorScheme.onSecondaryFixed }
          ColorRoleCard { roleName: "onSecondaryFixed";        roleColor: localColorScheme.onSecondaryFixed;        onRoleColor: localColorScheme.secondaryFixed }
          ColorRoleCard { roleName: "onSecondaryFixedVariant"; roleColor: localColorScheme.onSecondaryFixedVariant; onRoleColor: localColorScheme.secondaryFixed }
        }

        Text { text: "Tertiary"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "tertiary";            roleColor: localColorScheme.tertiary;            onRoleColor: localColorScheme.onTertiary }
          ColorRoleCard { roleName: "onTertiary";          roleColor: localColorScheme.onTertiary;          onRoleColor: localColorScheme.tertiary }
          ColorRoleCard { roleName: "tertiaryContainer";   roleColor: localColorScheme.tertiaryContainer;   onRoleColor: localColorScheme.onTertiaryContainer }
          ColorRoleCard { roleName: "onTertiaryContainer"; roleColor: localColorScheme.onTertiaryContainer; onRoleColor: localColorScheme.tertiaryContainer }
        }

        Text { text: "Tertiary Fixed"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "tertiaryFixed";          roleColor: localColorScheme.tertiaryFixed;          onRoleColor: localColorScheme.onTertiaryFixed }
          ColorRoleCard { roleName: "tertiaryFixedDim";       roleColor: localColorScheme.tertiaryFixedDim;       onRoleColor: localColorScheme.onTertiaryFixed }
          ColorRoleCard { roleName: "onTertiaryFixed";        roleColor: localColorScheme.onTertiaryFixed;        onRoleColor: localColorScheme.tertiaryFixed }
          ColorRoleCard { roleName: "onTertiaryFixedVariant"; roleColor: localColorScheme.onTertiaryFixedVariant; onRoleColor: localColorScheme.tertiaryFixed }
        }

        Text { text: "Error"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "error";            roleColor: localColorScheme.error;            onRoleColor: localColorScheme.onError }
          ColorRoleCard { roleName: "onError";          roleColor: localColorScheme.onError;          onRoleColor: localColorScheme.error }
          ColorRoleCard { roleName: "errorContainer";   roleColor: localColorScheme.errorContainer;   onRoleColor: localColorScheme.onErrorContainer }
          ColorRoleCard { roleName: "onErrorContainer"; roleColor: localColorScheme.onErrorContainer; onRoleColor: localColorScheme.errorContainer }
        }

        Text { text: "Surface"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "surface";                  roleColor: localColorScheme.surface;                  onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceDim";               roleColor: localColorScheme.surfaceDim;               onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceBright";            roleColor: localColorScheme.surfaceBright;            onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "onSurface";                roleColor: localColorScheme.onSurface;                onRoleColor: localColorScheme.surface }
          ColorRoleCard { roleName: "surfaceVariant";           roleColor: localColorScheme.surfaceVariant;           onRoleColor: localColorScheme.onSurfaceVariant }
          ColorRoleCard { roleName: "onSurfaceVariant";         roleColor: localColorScheme.onSurfaceVariant;         onRoleColor: localColorScheme.surfaceVariant }
          ColorRoleCard { roleName: "inverseSurface";           roleColor: localColorScheme.inverseSurface;           onRoleColor: localColorScheme.inverseOnSurface }
          ColorRoleCard { roleName: "inverseOnSurface";         roleColor: localColorScheme.inverseOnSurface;         onRoleColor: localColorScheme.inverseSurface }
          ColorRoleCard { roleName: "surfaceTint";              roleColor: localColorScheme.surfaceTint;              onRoleColor: localColorScheme.onSurface }
        }

        Text { text: "Surface Containers"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "surfaceContainerLowest";  roleColor: localColorScheme.surfaceContainerLowest;  onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceContainerLow";     roleColor: localColorScheme.surfaceContainerLow;     onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceContainer";        roleColor: localColorScheme.surfaceContainer;        onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceContainerHigh";    roleColor: localColorScheme.surfaceContainerHigh;    onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "surfaceContainerHighest"; roleColor: localColorScheme.surfaceContainerHighest; onRoleColor: localColorScheme.onSurface }
        }

        Text { text: "Background"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "background";   roleColor: localColorScheme.background;   onRoleColor: localColorScheme.onBackground }
          ColorRoleCard { roleName: "onBackground"; roleColor: localColorScheme.onBackground; onRoleColor: localColorScheme.background }
        }

        Text { text: "Outline"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "outline";        roleColor: localColorScheme.outline;        onRoleColor: localColorScheme.background }
          ColorRoleCard { roleName: "outlineVariant"; roleColor: localColorScheme.outlineVariant; onRoleColor: localColorScheme.background }
        }

        Text { text: "Utility"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "shadow"; roleColor: localColorScheme.shadow; onRoleColor: localColorScheme.background }
          ColorRoleCard { roleName: "scrim";  roleColor: localColorScheme.scrim;  onRoleColor: localColorScheme.background }
        }

        Text { text: "Palette Key Colors"; font.pixelSize: 14; font.weight: Font.Medium }
        Flow {
          Layout.fillWidth: true
          spacing: 8

          ColorRoleCard { roleName: "primaryPaletteKeyColor";        roleColor: localColorScheme.primaryPaletteKeyColor;        onRoleColor: localColorScheme.onPrimary }
          ColorRoleCard { roleName: "secondaryPaletteKeyColor";      roleColor: localColorScheme.secondaryPaletteKeyColor;      onRoleColor: localColorScheme.onSecondary }
          ColorRoleCard { roleName: "tertiaryPaletteKeyColor";       roleColor: localColorScheme.tertiaryPaletteKeyColor;       onRoleColor: localColorScheme.onTertiary }
          ColorRoleCard { roleName: "neutralPaletteKeyColor";        roleColor: localColorScheme.neutralPaletteKeyColor;        onRoleColor: localColorScheme.onSurface }
          ColorRoleCard { roleName: "neutralVariantPaletteKeyColor"; roleColor: localColorScheme.neutralVariantPaletteKeyColor; onRoleColor: localColorScheme.onSurfaceVariant }
        }

        Item { implicitHeight: 8 }
      }
    }
  }

  QtObject {
    id: d

    property color sourceColor
    property list<color> imageColors
  }
}
