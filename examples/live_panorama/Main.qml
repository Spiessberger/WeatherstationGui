import QtQuick

import LivePanorama
import wsgui.quick

Window {
  id: root

  width: 1024
  height: 400
  visible: true
  title: "Live Panorama"

  Backend {
    id: backend

    camId: 10040
    resolution: "fullsdf"
    fallbackResolution: "default"
  }

  PanoramaView {
    anchors.fill: parent

    imageTiles: backend.imageTiles
    autoScroll: true
  }
}
