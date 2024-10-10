import QtQuick
import WeatherstationGui

Item {
  id: root

  required property ColorSchemeProvider applicationSchemeProvider

  BackgroundImage {
    id: _backgroundImage

    camId: Settings.backgroundCamId
    thumbResolution: ImageResolution.Thumb
    imageResolutions: [ ImageResolution.Default, ImageResolution.Full ]
    onThumbImageTilesChanged: {
      if (thumbImageTiles.length > 0) {
        root.applicationSchemeProvider.loadSeedColorsFromImage(thumbImageTiles[0])
      }
      else {
        console.warn("no thumb image to load color scheme from")
      }
    }
  }

  PanoramaView {
    id: _panoramaView

    anchors.fill: parent

    autoScroll: true
    images: _backgroundImage.imageTiles
  }
}
