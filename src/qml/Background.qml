import QtQuick
import WeatherstationGui

Item {
  id: root

  BackgroundImage {
    id: _backgroundImage

    camId: Settings.backgroundCamId
    thumbResolution: ImageResolution.Thumb
    imageResolutions: [ ImageResolution.Default, ImageResolution.Full ]
  }

  PanoramaView {
    id: _panoramaView

    anchors.fill: parent

    autoScroll: true
    images: _backgroundImage.imageTiles
  }
}
