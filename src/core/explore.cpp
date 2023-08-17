#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>

#include "explore.h"

// Constructor to initialize animals from JSON file
Explore::Explore(const QString& filePath)
{
    loadActionsFromJson(filePath);
}

void Explore::loadActionsFromJson(const QString& filePath)
{
    QFile jsonFile(filePath);

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open actions JSON file");
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isNull() || !doc.isObject())
    {
        qWarning("Invalid JSON data");
        return;
    }

    QJsonObject jsonObj = doc.object();

    // Process explores
    QJsonArray exploreArray = jsonObj["Encounter"].toArray();
    for (const QJsonValue& exploreValue : exploreArray)
    {
        QJsonObject explore = exploreValue.toObject();
        QString encounterID = explore["ID"].toString();
        QString encounterName = explore["event_name"].toString();
        explores["Encounter"].append(encounterName);
    }

}

QString Explore::getRandomExplores(const QString& category) const
{
    QList<QString> exploresList = explores[category];
    if (!exploresList.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(exploresList.size());
        return exploresList[index];
    }
    return "";
}

