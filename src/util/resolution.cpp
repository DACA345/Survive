#include "resolution.h"

namespace Resolution
{
    QList<QSize> generateResolutions(int maxWidth, int maxHeight)
    {
        QList<QSize> resolutions;

        resolutions
            << QSize(640, 480)
            << QSize(800, 600)
            << QSize(1024, 768)
            << QSize(1280, 720)
            << QSize(1280, 800)
            << QSize(1366, 768)
            << QSize(1440, 900)
            << QSize(1600, 900)
            << QSize(1680, 1050)
            << QSize(1920, 1080)
            << QSize(2560, 1440)
            << QSize(2560, 1600)
            << QSize(3840, 2160)
            << QSize(5120, 2880)
            << QSize(7680, 4320)
            ;

        int maxSupportedIndex = 0;
        for (int i = 0; i < resolutions.size(); ++i)
        {
            QSize resolution = resolutions.at(i);
            if (resolution.width() > maxWidth || resolution.height() > maxHeight)
            {
                break;
            }
            maxSupportedIndex = i;
        }

        resolutions = resolutions.mid(0, maxSupportedIndex + 1);

        return resolutions;
    }
}