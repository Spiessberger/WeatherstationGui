import QtQuick

import WeatherstationGui 1.0

Item {
    id : root

    property TiledImageModel imageModel

    // values between 0 and 1, see Flickable::visibleArea
    property rect visibleArea
    // buffer for visible area in pixel
    property real visibleAreaBuffer: 0

    height: row.height
    width: row.width

    Row {
        id: row

        Repeater {
            id: repeater

            model: root.imageModel

            Item {
                id: imageTile

                width: model.width * d.scaleFactor
                height: model.height * d.scaleFactor

                property bool isVisible: {
                    if (root.visibleArea.width > 0) {
                        const left = imageTile.x / root.width
                        const right = left + imageTile.width / root.width
                        const buffer = root.visibleAreaBuffer / root.width

                        const visibleLeft = root.visibleArea.x
                        const visibleRight = root.visibleArea.x + root.visibleArea.width

                        return !(visibleRight < left - buffer|| visibleLeft > right + buffer)
                    }

                    return true
                }

                Image {
                    width: imageTile.width
                    height: imageTile.height
                    source: imageTile.isVisible ? model.source : ""
                    asynchronous: true
                }
            }
        }
    }

    QtObject {
        id: d

        property real scaleFactor: {
            if (!root.imageModel) {
                return 1.0
            }

            const sourceAspectRatio = root.imageModel.sourceSize.width / root.imageModel.sourceSize.height
            const rootItemAspectRatio = root.width / root.height

            if (rootItemAspectRatio > sourceAspectRatio) {
                return root.height / root.imageModel.sourceSize.height
            }
            else {
                return root.width / root.imageModel.sourceSize.width
            }
        }
    }
}
