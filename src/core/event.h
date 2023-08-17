#pragma once

#include <QString>
#include <QMap>

class Event {
public:
    // Constructor
    Event(const QString& filePath);

    // Load method
    void loadEventsFromJson(const QString& filePath);

    // Get random method 
    QString getRandomEvent() const;

    // Get season for the event
    QString getSeasonForEvent(const QString& eventDescription) const;

    // Added method to get effect
    QString getEffect(const QString& eventDescription) const;

    // Method to get random event for a given season
    QString getRandomEventForSeason(const QString& season) const;

private:

    struct EventData // Added this struct
    {
        QString season;
        QString effect;
    };

    QMap<QString, EventData> events;
};
