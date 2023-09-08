#pragma once

#include <QString>
#include <QMap>

/**
* @brief    This struct describes the EventEffect
*
*/
struct EventEffect
{
    int healthBar;
    int thirstBar;
    int hungerBar;
    int moraleBar;
    int energyBar;
};

/**
 * @brief   This struct describes the EventInfo
 * 
 */
struct EventInfo
{
    QString event;  
    QString season;
    EventEffect effect;
};

/**
 * @brief   This class describes the event instance
 * 
 */
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
    // Event elements
    QMap<QString, QList<EventInfo>> events;
};
