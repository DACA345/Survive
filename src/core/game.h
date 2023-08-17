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

#define MAX_TURNS 5
#define MIN_TURNS 0

class Game 
{
public:
    Game(const std::string& levelFolder);

    void run();

private:
    // Setter for where the location should be
    std::string levelFolder;
    QString convertQlevelFolder = QString::fromStdString(levelFolder);
    
    // Day counter
    int dayCounter;

    // Total Days survived counter
    int totalDays;

    // Month index to keep track of month
    int currentMonthIndex;

    // Array of month names
    static const std::string months[12];

    // Turn counter
    int turns;

    // Bool value to track if health is 0 or not
    bool alive;

    // Bool value to track if player can use that turn or not
    bool move;

    // float for tracking temps
    float maxTemperature;
    float avgTemperature;
    float minTemperature;

    // Var game bars
    Bar energyBar;
    Bar hungerBar;
    Bar thirstBar;
    Bar healthBar;

    // Var for climate data
    Day climate;

    // Var for animal data
    Animal animal;  

    // Var for plant data
    Plant plant;

    // Var for events
    Event events;

    // Var for seasons
    Season season; 

    // Var for explores
    Explore explore;

    bool isAlive() const;
    bool canMove() const;
    bool correctSeason(const QString& season) const;

    int getMenuChoice() const;
    void handleMenuChoice(int choice);

    void displayMainMenu() const;
    void displayDaySummary() const;
    void displayGameOver() const;
    void displayLevelIntro() const;

    void findFood();
    void findWater();
    void exploreOption();
    void rest();

    void updateMonth(); // Method to update the current month
    void updateTemperature(); // Method to update the temps
    void displayTemperature(); // Method to display temps
    void startNewDay(); // Starts a new day and update all necessary 

    void triggerEvent(); // Method to randomly trigger an event during beginning of the day
};



