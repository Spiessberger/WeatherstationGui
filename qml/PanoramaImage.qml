import QtQuick

import WeatherstationGui 1.0

Item {
    id : root

    property alias imageModel: repeater.model
    property real sourceWidth: 0
    property real sourceHeight: 0

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

            Rectangle {
                id: imageTile

                color: "red"
                border.color: "black"
                border.width: 2

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
            if (!root.imageModel ||
                    root.sourceWidth === 0 || root.sourceHeight === 0 ||
                    root.height === 0 || root.width === 0) {
                return 1.0
            }

            const sourceAspectRatio = root.sourceWidth / root.sourceHeight
            const rootItemAspectRatio = root.width / root.height

            if (rootItemAspectRatio > sourceAspectRatio) {
                return root.height / root.sourceHeight
            }
            else {
                return root.width / root.sourceWidth
            }
        }
    }
}
