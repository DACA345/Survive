#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
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
        actions["morale"].append(actDesc);
    }

    // Process food
    QJsonArray foodArray = jsonObj["food"].toArray();
    for (const QJsonValue& foodValue : foodArray)
    {
        QJsonObject food = foodValue.toObject();
        QString actionsID = food["actions_id"].toString();
        QString actDesc = food["act_desc"].toString();
        actions["food"].append(actDesc);
    }

    // Process water
    QJsonArray waterArray = jsonObj["water"].toArray();
    for (const QJsonValue& waterValue : waterArray)
    {
        QJsonObject water = waterValue.toObject();
        QString actionsID = water["actions_id"].toString();
        QString actDesc = water["act_desc"].toString();
        actions["water"].append(actDesc);
    }

    // Process explore
    QJsonArray exploreArray = jsonObj["explore"].toArray();
    for (const QJsonValue& exploreValue : exploreArray)
    {
        QJsonObject explore = exploreValue.toObject();
        QString actionsID = explore["actions_id"].toString();
        QString actDesc = explore["act_desc"].toString();
        actions["explore"].append(actDesc);
    }
}

QString Action::getRandomAction(const QString& category) const
{
    QList<QString> actionList = actions[category];
    if (!actionList.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(actionList.size());
        return actionList[index];
    }
    return "";
}


// getActionMethod to be implemented
//QString Action::getAction(const QString& category) const {
//    // Create a list to store available actions within the specified category
//    QList<QString> availableActions;
//
//    // Iterate through the actions map and filter actions by the given category
//    for (auto i = actions.cbegin(), end = actions.cend(); i != end; ++i) {
//        const QString& actionID = i.key();
//        const QString& actionDesc = i.value();
//        const QString& actionCategory = getCategoryByActionID(actionID); // Implement this function
//
//        if (actionCategory == category) {
//            availableActions.append(actionDesc);
//        }
//    }
//
//    // Randomly select an action description from the available actions
//    if (!availableActions.isEmpty()) {
//        int randomIndex = QRandomGenerator::global()->bounded(availableActions.size());
//        return availableActions[randomIndex];
//    }
//    else {
//        return ""; // No available actions in the given category
//    }
//}