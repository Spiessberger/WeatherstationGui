#pragma once

#include <QDate>
#include <QTime>

#include <vector>

namespace wsgui {
namespace panomax {

class PanomaxImageInfo
{
public:
    enum Resolution { Invalid, Full, Default };
    struct ImageSize
    {
        Resolution resolution = Invalid;
        int numTiles = 0;
    };

    PanomaxImageInfo();

    QDateTime recentImage() const;
    const std::vector<ImageSize> &imageSizes() const;

    bool loadImageInfo(const QByteArray &infoData);

    static QString resolutionString(Resolution resolution);

private:
    std::vector<ImageSize> m_imageSizes;
    QDateTime m_recentImage;
};

} // namespace panomax
} // namespace wsgui
