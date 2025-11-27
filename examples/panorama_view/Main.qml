import QtQuick
import QtQuick.Controls
import lib.wsgui_core

Window {
  width: 640
  height: 480
  visible: true
  title: qsTr("Hello World")

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

  PanoramaView {
    id: panoramaView

    anchors.fill: parent

    imageTiles: imageTiles1x6.imageTiles
    autoScroll: true
  }
}
