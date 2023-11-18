import QtQuick
import QtQuick.Window

import WeatherstationGui 1.0

Window {
    id: window

    title: "WeatherstationGui"
    width: 1280
    height: 800
    visible: true

    PanomaxImages {
        id: panomaxImages
    }

    PanoramaView {
        anchors.fill: parent
        imageModel: panomaxImages.recentImageModel
    }
}
