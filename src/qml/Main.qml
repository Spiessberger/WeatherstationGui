import QtQuick
import WeatherstationGui

Window {
  width: 640
  height: 480
  visible: true
  title: "Weatherstation Gui"

  RecentImage {
    id: _recentImage

    camId: Settings.backgroundCamId
    imageResolutions: [ ImageResolution.Default, ImageResolution.Full ]
  }

  PanoramaView {
    id: _panoramaView

    anchors.fill: parent

    autoScroll: true
    images: _recentImage.imageTiles
  }

  HomeScreen {
    anchors.fill: parent
  }
}
