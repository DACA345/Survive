#include <string>
#include "Day.h"
#include "Bar.h"
#include "Animal.h"
#include "Plant.h"
#include "Event.h"
#include "Action.h"

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

    // Array of month names
    static const std::string months[12];

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
    Event disasters;

    bool isAlive() const;
    bool canMove() const;

    int getMenuChoice() const;
    void handleMenuChoice(int choice);

    void displayMainMenu() const;
    void displayDaySummary() const;
    void displayGameOver() const;
    void displayLevelIntro() const;

    void findFood();
    void findWater();
    void explore();
    void rest();

    void updateMonth(); // Method to update the current month
    void updateTemperature(); // Method to update the temps
    void displayTemperature(); // Method to display temps
};



