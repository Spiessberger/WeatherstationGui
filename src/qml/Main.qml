import QtQuick
import WeatherstationGui

Window {
  width: 640
  height: 480
  visible: true
  title: "Weatherstation Gui"

  RecentImage {
    camId: Settings.backgroundCamId
    imageResolutions: [ ImageResolution.Default, ImageResolution.Full ]
  }
}
