#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

struct ActionInfo
{
    QString actionsID;
    QString actDesc;
    QString category;
};

class Action
{
public:
    // Constructor to initialize animals from JSON file
    Action(const QString& filePath);

    // Load animal data from JSON file
    void loadActionsFromJson(const QString& filePath);

    // Method to return action according to category and also it's status for edible or not
    const ActionInfo& getRandomAction() const;
    const ActionInfo& getRandomActionInCategory(const QString& category) const;
    QString getRandomActionCategory() const;

private:
    // Store actions categorized by categories
    QMap<QString, QList<ActionInfo>> actions;
};
