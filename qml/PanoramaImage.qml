import QtQuick

import WeatherstationGui 1.0

Item {
  id : root

  // Must provide roles
  //   source: path to image tile
  //   width: sourceWith of the image tile in pixel
  //   height: sourceHeight of the image tile in pixel
  property alias imageModel: repeater.model

  // combined width of all tiles contained in imageModel
  required property real sourceWidth
  // maximum height of tiles contained in imageModel
  required property real sourceHeight

  height: row.height
  width: row.width

  Row {
    id: row

    Repeater {
      id: repeater

      onCountChanged: console.log(count)

      Item {
        id: imageTile

        width: model.width * d.scaleFactor
        height: model.height * d.scaleFactor

        Image {
          width: imageTile.width
          height: imageTile.height
          source: model.source
          asynchronous: true
        }
      }
    }
  }

  QtObject {
    id: d

    // scale tile to fit into root item
    readonly property real scaleFactor: {
      if (!root.imageModel || root.sourceWidth === 0 || root.sourceHeight === 0 ||
          root.height === 0 || root.width === 0) {
        return 1.0
      }

      const sourceAspectRatio = root.sourceWidth / root.sourceHeight
      const rootItemAspectRatio = root.width / root.height

      if (rootItemAspectRatio > sourceAspectRatio) {
        return root.height / root.sourceHeight
      }
      else {
        return root.width / root.sourceWidth
      }
    }
  }
}
