import QtQuick
import WeatherstationGui

Item {
  id: root

  // image tiles for panorama image
  // std::vector<QImage>
  property alias images: _panoramaImage.images

  // autoscroll speed in pixel/second
  property real scrollVelocity: 50

  // defines if panoramaview scrolls through image
  property bool autoScroll: false

  // delay in milliseconds after which the panoramaview starts scrolling after user interaction
  // does nothing,if autoScroll is set to false
  property int autoScrollDelay: 5000

  PanoramaImage {
    id: _panoramaImage

    anchors.fill: parent
    xOffset: _flick.contentX

    onSourceSizeChanged: {
      if (root.autoScroll) {
        _scrollAnimation.from = _flick.contentX
        _scrollAnimation.startAnimation()
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

    onMovementEnded: {
      if (root.autoScroll) {
        _autoScrollTimer.start()
      }
    }
    onMovementStarted: {
      _autoScrollTimer.stop()
      _scrollAnimation.stop()
    }

    NumberAnimation on contentX {
      id: _scrollAnimation

      function startAnimation() {
        const pixelsToScroll = _scrollAnimation.to - _scrollAnimation.from

        if (pixelsToScroll > 0) {
          _scrollAnimation.stop()
          _scrollAnimation.duration = pixelsToScroll / root.scrollVelocity * 1000
          _scrollAnimation.start()
        }
      }

      from: 0
      to: _flick.contentWidth - _flick.width
      running: root.autoScroll

      onFinished: {
        from = 0
        startAnimation()
      }
    }
  }

  Timer {
    id: _autoScrollTimer

    interval: root.autoScrollDelay

    onTriggered: {
      if (root.autoScroll) {
        _scrollAnimation.from = _flick.contentX
        _scrollAnimation.startAnimation()
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
