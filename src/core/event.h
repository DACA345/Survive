#pragma once

#include <QString>
#include <QMap>

struct EventInfo
{
    QString event;
    QString season;
    QString effect;
};

class Event {
public:
    // Constructor
    Event(const QString& filePath);

    // Load method
    void loadEventsFromJson(const QString& filePath);

    QString getRandomSeason() const;

    // Get random method 
    EventInfo getRandomEvent() const;

    // Method to get random event for a given season
    EventInfo getRandomEventForSeason(const QString& season) const;

private:
    QMap<QString, QList<EventInfo>> events;
};
