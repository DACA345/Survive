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
 * @brief   This class contains the 
 * 
 */
class Explore
{
    public:
        /**
         * @brief      Constructs a new instance from a JSON of explore events.
         * @see        loadExploresFromJson 
         *
         * @param[in]  filePath  The file path
         */
        Explore(const QString& filePath);

        /**
         * @brief      loads the explore events from a JSON.
         *
         * @param[in]  filePath  The file path
         */
        void loadExploresFromJson(const QString& filePath);

        /**
         * @brief      Gets a random explore event.
         *
         * @return     The random explore event.
         */
        const ExploreInfo& getRandomExplore() const;

        /**
         * @brief      Gets a random explore event in a category.
         *
         * @param[in]  category  The category
         *
         * @return     The random explore event in the category.
         */
        const ExploreInfo& getRandomExploreInCategory(const QString& category) const;

        /**
         * @brief      Gets a random explore event category.
         *
         * @return     The random explore event category.
         */
        QString getRandomExploreCategory() const;

    private:
        /**
         * Stores the explore events per category.
         */
        QMap<QString, QList<ExploreInfo>> explores;
};
