#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
 * @brief   This struct describes the explore info
 * 
 */
struct ExploreInfo
{
    QString exploreID;
    QString eventName;
    QString category;
};

/**
 * @brief   This class describes the explore instance
 * 
 */
class Explore
{
public:
    // Constructor to initialize animals from JSON file
    Explore(const QString& filePath);

    // Load animal data from JSON file
    void loadExploresFromJson(const QString& filePath);

    // Method to return action according to category and also it's status for edible or not
    const ExploreInfo& getRandomExplore() const;
    const ExploreInfo& getRandomExploreInCategory(const QString& category) const;
    QString getRandomExploreCategory() const;

private:
    // Store explore categorized by categories
    QMap<QString, QList<ExploreInfo>> explores;
};
