import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import wsgui

Item {
  WeatherDataModel {
    id: _weatherDataModel

    from: new Date("2023-03-19 11:28:52")
    to: new Date()
  }

  Column {
    anchors.left: parent.left
    anchors.top: parent.top
  }

  HorizontalHeaderView {
    id: _header

    anchors.left: _tableView.left
    anchors.top: parent.top
    anchors.margins: 16

    syncView: _tableView
    clip: true
    resizableColumns: false
    textRole: "displayData"
  }

  TableView {
    id: _tableView

    anchors.top: _header.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 16

    ScrollBar.vertical: ScrollBar {
      id: _scrollBar
    }

    flickableDirection: Flickable.VerticalFlick
    clip: true
    model: _weatherDataModel

    delegate: ItemDelegate {
      required property var displayData
      text: displayData

      Rectangle {
        id: _divider

        anchors.top: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height: 1

        color: Theme.outlineVariant
      }
    }

    columnWidthProvider: function(column) {
      if (column === WeatherDataModel.Timestamp) {
        return 150
      }
      else {
        const availableWidth = _tableView.width - 150 - _scrollBar.width
        return availableWidth / (_tableView.columns - 1)
      }
    }
  }
}
