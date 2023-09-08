#pragma once

#include <QMap>
#include <QString>
#include <QList>
#include <QPair>

/**
 * @brief      Struct representation of the JSON action info.
 */
struct ActionInfo
{
    QString actionsID;
    QString actDesc;
    QString category;
};

/**
 * @brief      This class contains the actions from a JSON.
 */
class Action
{
public:
    /**
     * @brief      Constructs a new instance from a JSON of actions.
     * @see        loadActionsFromJson
     *
     * @param[in]  filePath  The file path
     */
    Action(const QString& filePath);

    /**
     * @brief      Loads the actions from json.
     *
     * @param[in]  filePath  The file path
     */
    void loadActionsFromJson(const QString& filePath);

    /**
     * @brief      Gets a random action.
     *
     * @return     The random action.
     */
    const ActionInfo& getRandomAction() const;

    /**
     * @brief      Gets a random action in category.
     *
     * @param[in]  category  The category
     *
     * @return     The random action in the category.
     */
    const ActionInfo& getRandomActionInCategory(const QString& category) const;

    /**
     * @brief      Gets a random category of actions.
     *
     * @return     The random action category.
     */
    QString getRandomActionCategory() const;

private:
    /**
     * Stores the actions per category.
     */
    QMap<QString, QList<ActionInfo>> actions;
};
