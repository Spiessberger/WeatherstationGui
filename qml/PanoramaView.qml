import QtQuick

import WeatherstationGui 1.0

Item {
    id: root

    property TiledImageModel imageModel

    ImageWrapProxyModel {
        id: imageWrapModel
        sourceModel: root.imageModel
        sourceWidth: root.imageModel ? root.imageModel.sourceWidth + root.width / d.scaleFactor / d.baseScaleFactor : 0
    }

    Flickable {
      id: flick
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width
      height: parent.height

      contentHeight: d.initialHeight
      contentWidth: d.initialWidth

      boundsMovement: Flickable.StopAtBounds

      PanoramaImage {
        id : panoramaImage

        width: parent.width
        height: parent.height
        imageModel: imageWrapModel
        sourceWidth: imageWrapModel.sourceWidth
        sourceHeight: root.imageModel ? root.imageModel.sourceHeight : 0
        visibleArea: Qt.rect(flick.visibleArea.xPosition, flick.visibleArea.yPosition, flick.visibleArea.widthRatio, flick.visibleArea.heightRatio)
        visibleAreaBuffer: 500

        MouseArea {
          id: mouseArea
          anchors.fill: parent
          acceptedButtons: Qt.AllButtons
          onWheel: (wheel) => {
                     d.scaleFactor = Math.max(1, (d.scaleFactor * (1 + wheel.angleDelta.y / 1000)))

                     const newHeight = d.initialHeight * d.scaleFactor
                     const newWidth = d.initialWidth * d.scaleFactor

                     flick.resizeContent(newWidth, newHeight, Qt.point(wheel.x, wheel.y))
                   }
        }
      }
    }

    QtObject {
      id: d

      property real scaleFactor: 1.0

      readonly property real baseScaleFactor: panoramaImage.sourceHeight > 0 ? flick.height / panoramaImage.sourceHeight : 1
      readonly property real initialWidth: root.imageModel ? d.baseScaleFactor * panoramaImage.sourceWidth : 0
      readonly property real initialHeight: flick.height
    }
}
