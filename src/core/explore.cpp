#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include <QRandomGenerator>

#include "explore.h"

// Constructor to initialize animals from JSON file
Explore::Explore(const QString& filePath)
{
    loadExploresFromJson(filePath);
}

void Explore::loadExploresFromJson(const QString& filePath)
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

    // Process encounter
    QJsonArray encounterArray = jsonObj["encounter"].toArray();
    for (const QJsonValue& encounterValue : encounterArray)
    {
        QJsonObject encounter = encounterValue.toObject();
        QString exploreID = encounter["explore_ID"].toString();
        QString eventName = encounter["event_name"].toString();
        explores["encounter"].append(ExploreInfo{ exploreID, "encounter", eventName });
    }

    // Process see
    QJsonArray seeArray = jsonObj["see"].toArray();
    for (const QJsonValue& seeValue : seeArray)
    {
        QJsonObject see = seeValue.toObject();
        QString exploreID = see["explore_ID"].toString();
        QString eventName = see["event_name"].toString();
        explores["see"].append(ExploreInfo{ exploreID, "see", eventName });
    }

    // Process find
    QJsonArray findArray = jsonObj["find"].toArray();
    for (const QJsonValue& findValue : findArray)
    {
        QJsonObject find = findValue.toObject();
        QString exploreID = find["explore_ID"].toString();
        QString eventName = find["event_name"].toString();
        explores["find"].append(ExploreInfo{ exploreID, "find", eventName });
    }

    // Process observe
    QJsonArray observeArray = jsonObj["observe"].toArray();
    for (const QJsonValue& observeValue : observeArray)
    {
        QJsonObject observe = observeValue.toObject();
        QString exploreID = observe["actions_id"].toString();
        QString eventName = observe["act_desc"].toString();
        explores["observe"].append(ExploreInfo{ exploreID, "observe", eventName });
    }
}

const ExploreInfo& Explore::getRandomExplore() const
{
    return getRandomExploreInCategory(getRandomExploreCategory());
}

// Method to print our random explore according to category
const ExploreInfo& Explore::getRandomExploreInCategory(const QString& category) const
{
    const QList<ExploreInfo>& exploreList = explores[category];
    if (exploreList.isEmpty())
    {
        qFatal("No explore found");
    }

    return exploreList[QRandomGenerator::global()->bounded(exploreList.size())];
}

QString Explore::getRandomExploreCategory() const
{
    const QList<QString>& exploreCategory = explores.keys();
    if (exploreCategory.isEmpty())
    {
        qFatal("No explores found");
    }

    return exploreCategory[QRandomGenerator::global()->bounded(exploreCategory.size())];
}