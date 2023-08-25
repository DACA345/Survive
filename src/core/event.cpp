#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include "event.h"

// Constructor that takes a file path to load events from a JSON file.
Event::Event(const QString& filePath) {
    loadEventsFromJson(filePath);
}

// Function to load events from a JSON file.
void Event::loadEventsFromJson(const QString& filePath) {
    // Open the JSON file.
    QFile jsonFile(filePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Could not open events JSON file");
        return;
    }

    // Read the JSON data from the file.
    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    // Check if the JSON data is an array.
    if (doc.isArray()) 
    {
        QJsonArray jsonArray = doc.array();

        // Iterate through each event object in the array.
        for (const QJsonValue& eventValue : jsonArray) {
            QJsonObject eventObject = eventValue.toObject();

            // Extract description, season, and effect from the event object.
            QString eventDesc = eventObject["event_desc"].toString();
            QString eventSeason = eventObject["season"].toString();
            QString eventEffect = eventObject["effect"].toString(); // Added this line

            if (!events.contains(eventSeason))
            {
                events[eventSeason] = QList<EventInfo>();
            }

            // Store the event information in the 'events' QMap.
            EventInfo eventData;
            eventData.event = eventDesc;
            eventData.season = eventSeason;
            eventData.effect = eventEffect; // Added this line
            events[eventSeason].append(eventData);
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}

QString Event::getRandomSeason() const
{
    const QList<QString>& seasons = events.keys();
    if (seasons.empty())
    {
        qFatal("No seasons found");
    }

    int randomIndex = QRandomGenerator::global()->bounded(seasons.size());
    return seasons[randomIndex];
}

// Function to retrieve a random event description.
const EventInfo& Event::getRandomEvent() const
{
    return getRandomEventForSeason(getRandomSeason());
}

// Function to retrieve a random event based on season.
const EventInfo& Event::getRandomEventForSeason(const QString& season) const
{
    const QList<EventInfo>& matchingEvents = events[season];

    int randomIndex = QRandomGenerator::global()->bounded(matchingEvents.size());
    return matchingEvents[randomIndex];
}