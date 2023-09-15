#pragma once

#include <QString>
#include <QMap>

#include "effect.h"

/**
 * @brief   This struct describes the EventInfo
 * 
 */
struct EventInfo
{
    QString event;  
    QString season;
    Effect effect;
};

/**
 * @brief   This class contains the events.
 * 
 */
class Event {
    public:
        /**
         * @brief      Constructs a new instance from a JSON of events.
         * @see        loadEventsFromJson
         *
         * @param[in]  filePath  The file path
         */
        Event(const QString& filePath);

        /**
         * @brief      Loads the events from json.
         *
         * @param[in]  filePath  The file path
         */
        void loadEventsFromJson(const QString& filePath);

        /**
         * @brief      Gets a random season.
         *
         * @return     The random season.
         */
        QString getRandomSeason() const;

        /**
         * @brief      Gets a random event.
         *
         * @return     The random event.
         */
        const EventInfo& getRandomEvent() const;

        /**
         * @brief      Gets a random event for a season.
         *
         * @param[in]  season  The season
         *
         * @return     The random event.
         */
        const EventInfo& getRandomEventForSeason(const QString& season) const;

    private:
        /**
         * Stores the events per season.
         */
        QMap<QString, QList<EventInfo>> events;
};
