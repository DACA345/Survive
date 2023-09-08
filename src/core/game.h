#pragma once

#include <string>
#include "day.h"
#include "bar.h"
#include "animal.h"
#include "plant.h"
#include "event.h"
#include "action.h"
#include "season.h"
#include "explore.h"
#include "action.h"

#define MAX_TURNS 5
#define MIN_TURNS 0

/**
 * @brief   This class describes the game instance
 * 
 */
class Game 
{
public:
    /**
     * @brief      Constructs a new game instance.
     *
     * @param[in]  levelFolder  The level folder
     */
    Game(const std::string& levelFolder);

    /**
     * @brief      Runs the game.
     */
    void run();

private:
    /**
     * Array of month IDs.
     */
    static const std::string months[12];

    /**
     * Folder where level data is stored.
     */
    std::string levelFolder;

    /**
     * QString levelFolder
     * @see levelFolder
     */
    QString convertQlevelFolder = QString::fromStdString(levelFolder);
    
    /**
     * Current day.
     */
    int dayCounter;

    /**
     * Days survived.
     */
    int totalDays;

    /**
     * Current month.
     */
    int currentMonthIndex;

    /**
     * Current turns left.
     */
    int turns;

    /**
     * Whether the user is alive
     */
    bool alive;

    /**
     * Whether the player can do an action.
     */
    bool move;

    /**
     * Max temperature for a season.
     */
    float maxTemperature;

    /**
     * Average temperature for a season.
     */
    float avgTemperature;

    /**
     * Min temperature for a season.
     */
    float minTemperature;

    /**
     * The user's energy bar.
     */
    Bar energyBar;

    /**
     * The user's hunger bar.
     */
    Bar hungerBar;

    /**
     * The user's thirst bar.
     */
    Bar thirstBar;

    /**
     * The user's health bar.
     */
    Bar healthBar;
    Bar moraleBar;

    /**
     * The day containing climate data.
     */
    Day climate;

    /**
     * Animal info.
     */
    Animal animal;  

    /**
     * Plant info.
     */
    Plant plant;

    /**
     * Event info.
     */
    Event events;

    /**
     * Season info.
     */
    Season season; 

    /**
     * Explore events info.
     */
    Explore explore;

    /**
     * Action info.
     */
    Action action;

    /**
     * @brief      Determines if the user is alive.
     *
     * @return     True if alive, False otherwise.
     */
    bool isAlive() const;

    /**
     * @brief      Determines the ability to do an action.
     *
     * @return     True if able to, False otherwise.
     */
    bool canMove() const;

    /**
     * @brief      Checks if a season is the current season.
     *
     * @param[in]  season  The season to check against
     *
     * @return     True if it is that season, false otherwise.
     */
    bool correctSeason(const QString& season) const;

    /**
     * @brief      Gets the user's menu choice.
     *
     * @return     The menu choice.
     */
    int getMenuChoice() const;
    
    /**
     * @brief      Handles the user's menu choice.
     *
     * @param[in]  choice  The choice
     */
    void handleMenuChoice(int choice);

    /**
     * @brief      Displays the main menu options.
     */
    void displayMainMenu() const;

    /**
     * @brief      Displays the day summary.
     */
    void displayDaySummary() const;

    /**
     * @brief      Display the game over screen.
     */
    void displayGameOver() const;

    /**
     * @brief      Displays the level intro.
     */
    void displayLevelIntro() const;

    /**
     * @brief      Action for finding food.
     */
    void findFood();

    /**
     * @brief      Action for finding water.
     */
    void findWater();

    /**
     * @brief      Action for exploring.
     */
    void exploreOption();

    /**
     * @brief      Action for resting.
     */
    void relax();
    
    /**
     * @brief      Updates the month.
     */
    void updateMonth();

    /**
     * @brief      Updates the temperature.
     */
    void updateTemperature();

    /**
     * @brief      Displays the current temperature.
     */
    void displayTemperature();

    /**
     * @brief      Starts a new day.
     */
    void startNewDay();

    /**
     * @brief      Triggers an event.
     */
    void triggerEvent();
};



