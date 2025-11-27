import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import lib.wsgui_core

Window {
  width: 640
  height: 480
  visible: true
  title: qsTr("Panorama View")

  ImageTilesFileLoader {
    id: imageTiles1x6

    fileNames: [
      "qrc:/qt/qml/PanoramaView/tiles/tile_0.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_1.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_2.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_3.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_4.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_5.png",
    ]

    rows: 1
  }

  ImageTilesFileLoader {
    id: imageTiles2x4

    fileNames: [
      "qrc:/qt/qml/PanoramaView/tiles/tile_0.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_1.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_2.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_3.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_4.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_5.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_6.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_7.png"
    ]

    rows: 2
  }

  ImageTilesFileLoader {
    id: imageTiles3x3

    fileNames: [
      "qrc:/qt/qml/PanoramaView/tiles/tile_0.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_1.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_2.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_3.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_4.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_5.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_6.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_7.png",
      "qrc:/qt/qml/PanoramaView/tiles/tile_8.png"
    ]

    rows: 3
  }

  PanoramaView {
    id: panoramaView

    anchors.fill: parent

    imageTiles: d.tiles[d.currentTilesIndex]
    autoScroll: true
  }

  Button {
    text: "Next"
    onClicked: d.currentTilesIndex = (d.currentTilesIndex + 1) % d.tiles.length
  }

  QtObject {
    id: d

    property int currentTilesIndex: 0
    readonly property var tiles: [
      imageTiles1x6.imageTiles,
      imageTiles2x4.imageTiles,
      imageTiles3x3.imageTiles
    ]
  }
}
