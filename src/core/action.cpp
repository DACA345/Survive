#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include <QRandomGenerator>

#include "action.h"

// Constructor to initialize animals from JSON file
Action::Action(const QString& filePath)
{
    loadActionsFromJson(filePath);
}

void Action::loadActionsFromJson(const QString& filePath)
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

    // Process morale
    QJsonArray moraleArray = jsonObj["morale"].toArray();
    for (const QJsonValue& moraleValue : moraleArray)
    {
        QJsonObject morale = moraleValue.toObject();
        QString actionsID = morale["actions_id"].toString();
        QString actDesc = morale["act_desc"].toString();
        actions["morale"].append(ActionInfo{ actionsID, "morale", actDesc });
    }

    // Process food
    QJsonArray foodArray = jsonObj["food"].toArray();
    for (const QJsonValue& foodValue : foodArray)
    {
        QJsonObject food = foodValue.toObject();
        QString actionsID = food["actions_id"].toString();
        QString actDesc = food["act_desc"].toString();
        actions["food"].append(ActionInfo{ actionsID, "food", actDesc });
    }

    // Process water
    QJsonArray waterArray = jsonObj["water"].toArray();
    for (const QJsonValue& waterValue : waterArray)
    {
        QJsonObject water = waterValue.toObject();
        QString actionsID = water["actions_id"].toString();
        QString actDesc = water["act_desc"].toString();
        actions["water"].append(ActionInfo{ actionsID, "water", actDesc });
    }

    // Process explore
    QJsonArray exploreArray = jsonObj["explore"].toArray();
    for (const QJsonValue& exploreValue : exploreArray)
    {
        QJsonObject explore = exploreValue.toObject();
        QString actionsID = explore["actions_id"].toString();
        QString actDesc = explore["act_desc"].toString();
        actions["explore"].append(ActionInfo{ actionsID, "explore", actDesc });
    }
}

const ActionInfo& Action::getRandomAction() const
{
    return getRandomActionInCategory(getRandomActionCategory());
}

// Method to print our random action according to category
const ActionInfo& Action::getRandomActionInCategory(const QString& category) const
{
    const QList<ActionInfo>& actionList = actions[category];
    if (actionList.isEmpty())
    {
        qFatal("No animal found");
    }

    return actionList[QRandomGenerator::global()->bounded(actionList.size())];
}

QString Action::getRandomActionCategory() const
{
    const QList<QString>& actionCategory = actions.keys();
    if (actionCategory.isEmpty())
    {
        qFatal("No actions found");
    }

    return actionCategory[QRandomGenerator::global()->bounded(actionCategory.size())];
}