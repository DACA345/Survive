#pragma once

#include <QMap>

/**
 * @brief   This class describes the season instance
 * 
 */
class Season {
public:
    Season(const QString& filename);

    QString getSeason(const QString& month) const;

    QStringList getMonth(const QString& season) const;

private:
    QMap<QString, QString> monthToSeason;
};
