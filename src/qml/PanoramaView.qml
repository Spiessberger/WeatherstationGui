import QtQuick
import WeatherstationGui

Item {
  id: root

  property alias images: _panoramaImage.images
  property real scrollVelocity: 50
  property bool autoScroll: false

  PanoramaImage {
    id: _panoramaImage

    anchors.fill: parent
    xOffset: _flick.contentX

    onSourceSizeChanged: {
      if (root.autoScroll) {
        _scrollAnimation.startFromCurrentPosition()
      }
    }
  }

  Flickable {
    id: _flick

    anchors.fill: parent

    boundsMovement: Flickable.StopAtBounds

    contentWidth: {
      if (_panoramaImage.sourceSize.width === 0) {
        return 0
      }
      return _panoramaImage.sourceSize.width * d.scale + _flick.width
    }
    contentHeight: _panoramaImage.sourceSize.height * d.scale

    onHorizontalOvershootChanged: {
      if (horizontalOvershoot === 0) {
        return
      }

      const horizontalVelocity = _flick.horizontalVelocity

      if (horizontalOvershoot > 0) {
        _flick.contentX = 0
      }
      else if (horizontalOvershoot < 0) {
        _flick.contentX = _flick.contentWidth - _flick.width
      }

      _flick.flick(-horizontalVelocity, 0)
    }

    NumberAnimation on contentX {
      id: _scrollAnimation

      function startFromCurrentPosition() {
        const pixelsToScroll = _scrollAnimation.to - _scrollAnimation.from

        if (pixelsToScroll > 0) {
          _scrollAnimation.duration = pixelsToScroll / root.scrollVelocity * 1000
          _scrollAnimation.start()
        }
      }

      from: 0
      to: _flick.contentWidth - _flick.width
      running: root.autoScroll

      onFinished: {
        from = 0
        startFromCurrentPosition()
      }
    }
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
