import QtQuick

import WeatherstationGui 1.0

Item {
    id: root

    property TiledImageModel imageModel

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
        imageModel: root.imageModel
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
      property real initialWidth: flick.height / imageModel.sourceSize.height * imageModel.sourceSize.width
      property real initialHeight: flick.height
    }
}
