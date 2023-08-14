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
    if (doc.isArray()) {
        QJsonArray jsonArray = doc.array();

        // Iterate through each event object in the array.
        for (const QJsonValue& eventValue : jsonArray) {
            QJsonObject eventObject = eventValue.toObject();

            // Extract event ID and description from the event object.
            QString eventId = eventObject["event_id"].toString();
            QString eventDesc = eventObject["event_desc"].toString();

            // Store the event information in the 'events' QMap.
            events[eventId] = eventDesc;
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}

// Function to print all events stored in the 'events' QMap.
void Event::printAllEvents() const
{
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        std::cout << "Event ID: " << it.key().toStdString() << std::endl;
        std::cout << "Event Description: " << it.value().toStdString() << std::endl;
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
        return it.value();
    }
    return QString(); // Return an empty string if there are no events
}

// Function to print a random event's ID and description.
void Event::printRandomEvent() const
{
    if (!events.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(events.size());
        auto it = events.begin();
        std::advance(it, randomIndex);

        std::cout << "Random Event ID: " << it.key().toStdString() << std::endl;
        std::cout << "Random Event Description: " << it.value().toStdString() << std::endl;
    }
    else
    {
        std::cout << "No events available." << std::endl;
    }
}
