import QtQuick
import WeatherstationGui

Item {
  id: root

  BackgroundImage {
    id: _backgroundImage

    camId: Settings.backgroundCamId
    thumbResolution: ImageResolution.Thumb
    imageResolutions: [ ImageResolution.Default, ImageResolution.Full ]
    onThumbImageTilesChanged: {
      if (thumbImageTiles.length > 0) {
        _colorSchemeProvider.loadSeedColorsFromImage(thumbImageTiles[0])
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

  ColorSchemeProvider {
    id: _colorSchemeProvider

    onSeedColorsChanged: {
      if (seedColors.length > 0) {
        loadSchemeFromColor(seedColors[0], Settings.isDarkScheme, Settings.schemeContrast)
      }
      else {
        console.warn("no seed colors to load color scheme from")
      }
    }

    onColorsChanged: Theme.updateThemeColors(colorScheme)
  }
}
