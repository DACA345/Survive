#include "Event.h"
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

Event::Event(const QString& filePath) {
    loadEventsFromJson(filePath);
}

void Event::loadEventsFromJson(const QString& filePath) {
    QFile jsonFile(filePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Could not open events JSON file");
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isArray()) {
        QJsonArray jsonArray = doc.array();
        for (const QJsonValue& eventValue : jsonArray) {
            QJsonObject eventObject = eventValue.toObject();

            QString eventId = eventObject["event_id"].toString();
            QString eventDesc = eventObject["event_desc"].toString();

            events[eventId] = eventDesc;
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}


void Event::printAllEvents() const
{
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        std::cout << "Event ID: " << it.key().toStdString() << std::endl;
        std::cout << "Event Description: " << it.value().toStdString() << std::endl;
    }
}

QString Event::getRandomEvent() const
{
    if (!events.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(events.size());
        auto it = events.begin();
        std::advance(it, randomIndex);
        return it.value();
    }
    return QString(); // Return an empty string if there are no events
}

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
