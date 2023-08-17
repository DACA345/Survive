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

            // Store the event information in the 'events' QMap.
            EventData eventData;
            eventData.season = eventSeason;
            eventData.effect = eventEffect; // Added this line
            events[eventDesc] = eventData;
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}

// Function to retrieve a random event description.
QString Event::getRandomEvent() const
{
    if (!events.isEmpty())
    {
        // Generate a random index within the range of available events.
        int randomIndex = QRandomGenerator::global()->bounded(events.size());
        auto it = events.begin();
        std::advance(it, randomIndex);

        // Return the description of the randomly selected event.
        return it.key();
    }
    return QString(); // Return an empty string if there are no events
}

// In your Event.cpp file, implement the new method:
QString Event::getSeasonForEvent(const QString& eventDescription) const
{
    auto it = events.find(eventDescription);
    if (it != events.end()) {
        return it.value().season;
    }
    else 
    {
        return "No available seasons";
    }
}

// Function to retrieve the effect of an event.
QString Event::getEffect(const QString& eventDescription) const
{
    auto it = events.find(eventDescription);
    if (it != events.end()) 
    {
        return it.value().effect;
    }
    else
    {
        return "No effect available";
    }
}

// Function to retrieve a random event based on season.
QString Event::getRandomEventForSeason(const QString& season) const
{
    QVector<QString> matchingEvents;

    for (auto it = events.begin(); it != events.end(); ++it)
    {
        if (it.value().season == season)
        {
            matchingEvents.push_back(it.key());
        }
    }

    if (!matchingEvents.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(matchingEvents.size());
        return matchingEvents[randomIndex];
    }

    return QString(); // Return an empty string if no matching events found
}