#pragma once
#include <QList>
#include <QSize>

namespace Resolution
{
    QList<QSize> generateResolutions(int maxWidth, int maxHeight);
}