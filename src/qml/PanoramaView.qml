import QtQuick
import WeatherstationGui

Item {
  id: root

  property alias images: _panoramaImage.images

  PanoramaImage {
    id: _panoramaImage

    anchors.fill: parent
    xOffset: _flick.contentX
  }

  Flickable {
    id: _flick

    anchors.fill: parent

    boundsBehavior: Flickable.StopAtBounds

    contentWidth: {
      if (_panoramaImage.sourceSize.width === 0) {
        return 0
      }
      return _panoramaImage.sourceSize.width * d.scale + _flick.width
    }
    contentHeight: _panoramaImage.sourceSize.height * d.scale
  }

  QtObject {
    id: d

    readonly property real scale: {
      if (_panoramaImage.sourceSize.height === 0) {
        return 0
      }
      return root.height / _panoramaImage.sourceSize.height
    }
  }
}
