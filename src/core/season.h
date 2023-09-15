#pragma once

#include <QMap>

/**
 * @brief   This class describes the season instance
 * 
 */
class Season {
public:
    /**
     * @brief      Constructs a new instance of season data from a JSON.
     *
     * @param[in]  filename  The filename
     */
    Season(const QString& filename);

    /**
     * @brief      Gets the season of a month.
     *
     * @param[in]  month  The month
     *
     * @return     The season.
     */
    QString getSeason(const QString& month) const;

    /**
     * @brief      Gets the months of a season.
     *
     * @param[in]  season  The season
     *
     * @return     The month.
     */
    QStringList getMonth(const QString& season) const;

private:
    /**
     * Maps the months to a season.
     */
    QMap<QString, QString> monthToSeason;
};
