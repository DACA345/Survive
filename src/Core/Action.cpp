#include <Action.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>

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
        }
    }
    else {
        qWarning("Invalid JSON data");
    }
}
