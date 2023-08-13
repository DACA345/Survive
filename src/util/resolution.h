#pragma once
#include <QList>
#include <QSize>

namespace Resolution
{
    /**
     * @brief      Generate a list of common resolutions.
     *
     * @param[in]  maxWidth   The maximum width
     * @param[in]  maxHeight  The maximum height
     *
     * @return     List of resolutions.
     */
    QList<QSize> generateResolutions(int maxWidth, int maxHeight);
}