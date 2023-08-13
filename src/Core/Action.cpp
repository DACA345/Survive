#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator> 

#include "Action.h"

// Constructor that takes a file path to load events from a JSON file.
Action::Action(const QString& filePath) {
    loadActionsFromJson(filePath);
}

// Function to load events from a JSON file.
void Action::loadActionsFromJson(const QString& filePath) {
    // Open the JSON file.
    QFile jsonFile(filePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Could not open actions JSON file");
        return;
    }

    // Read the JSON data from the file.
    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    // Check if the JSON data is an array.
    if (doc.isArray()) {
        QJsonArray jsonArray = doc.array();

        // Iterate through each event object in the array.
        for (const QJsonValue& actionValue : jsonArray) {
            QJsonObject actionObject = actionValue.toObject();

            // Extract event ID and description from the event object.
            QString actionCategory = actionObject["category"].toString();
            QString actionID = actionObject["actions_id"].toString();
            QString actionDesc = actionObject["act_desc"].toString();
            

            // Store the event information in the 'events' QMap.
            actions[actionID] = actionDesc;
            actionCategories[actionID] = actionCategory;
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}

QString Action::getAction(const QString& category) const {
    // Create a list to store available actions within the specified category
    QList<QString> availableActions;

    // Iterate through the actions map and filter actions by the given category
    for (auto i = actions.cbegin(), end = actions.cend(); i != end; ++i) {
        const QString& actionID = i.key();
        const QString& actionDesc = i.value();
        const QString& actionCategory = getCategoryByActionID(actionID); // Implement this function

        if (actionCategory == category) {
            availableActions.append(actionDesc);
        }
    }

    // Randomly select an action description from the available actions
    if (!availableActions.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(availableActions.size());
        return availableActions[randomIndex];
    }
    else {
        return ""; // No available actions in the given category
    }
}

QString Action::getCategoryByActionID(const QString& actionID) const {
    if (actionCategories.contains(actionID)) {
        return actionCategories[actionID];
    }
    else {
        return ""; // Action ID not found
    }
}

