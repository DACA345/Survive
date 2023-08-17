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
    const EventInfo& getRandomEvent() const;

    // Method to get random event for a given season
    const EventInfo& getRandomEventForSeason(const QString& season) const;

private:
    QMap<QString, QList<EventInfo>> events;
};
