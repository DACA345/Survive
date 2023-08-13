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
    
    // Var game bars
    Bar energyBar;
    Bar hungerBar;
    Bar thirstBar;

    // Var for climate data
    Day climate;

    // Var for animal data
    Animal animal;  

    // Var for plant data
    Plant plant;

    // Var for events
    Event disasters;


    int getMenuChoice() const;
    void handleMenuChoice(int choice);

    void displayMainMenu() const;
    void displayDaySummary() const;
    void displayGameOver() const;
    void displayLevelIntro() const;
    void displayActionsMenu() const;
    void displayEvents() const;

};



