#include "Game.h"
#include <iostream>
#include <string>

Game::Game(const std::string& levelFolder) : levelFolder(levelFolder),
climate(levelFolder + "/climate.json"), // Initialize climate data
animal(convertQlevelFolder + "/animals.json"), // Initialize animal
plant(convertQlevelFolder + "/plants.json"), // Initialize Plant
disasters(convertQlevelFolder + "/disaster_ev.json") // Initialize Disaster

{
    // Initialize Bar
    Bar energyBar(5);
    Bar hungerBar(10);
    Bar thirstBar(10);

    dayCounter = 1; // Start with Day 1
    turns = 5; // Initialize turns to 5

    std::cout << "Game initialized for level: " << levelFolder << std::endl;
}


void Game::run()
{
    displayLevelIntro();

    while (true) 
    {
        std::cout << "Day: " << dayCounter << std::endl;
        std::cout << "Turns remaining: " << turns << std::endl;
        displayMainMenu();
        int choice = getMenuChoice();
        handleMenuChoice(choice);

        if (turns == 1) {
            std::cout << "Only 1 turn remaining!" << std::endl;
        }
        else if (turns == 0) {
            displayDaySummary();
            std::cout << "Day " << dayCounter << " ends!" << std::endl;
            ++dayCounter; // Increment the day counter
            turns = 5; // Reset the turn counter
        }

        std::cout << "*********************************" << std::endl;
    }
}

int Game::getMenuChoice() const
{
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

void Game::displayMainMenu() const
{
    // Display the main menu options
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. Find Food" << std::endl;
    std::cout << "2. Find Water" << std::endl;
    std::cout << "3. Explore" << std::endl;
    std::cout << "4. Rest" << std::endl;
}

void Game::handleMenuChoice(int choice)
{
    switch (choice) {
    case 1:
        --turns; // Deduct a turn when a valid action is chosen
        break;
    case 2:
        --turns; // Deduct a turn when a valid action is chosen
        break;
    case 3:
        --turns; // Deduct a turn when a valid action is chosen
        break;
    case 4:
        --turns; // Deduct a turn when a valid action is chosen
        break;
    default:
        std::cout << "Invalid choice. Please select a valid option." << std::endl;
    }
}

void Game::displayDaySummary() const
{
    std::cout << "*********************************" << std::endl;
    // Display the summary for the day
    std::cout << "Day Summary:" << std::endl;
    // Display energy, hunger, thirst bars
    std::cout << "Energy: " << energyBar.getValue() << "/ 10" << std::endl;
    std::cout << "Hunger: " << hungerBar.getValue() << "/ 10" << std::endl;
    std::cout << "Thirst: " << thirstBar.getValue() << "/ 10" << std::endl;
    // Display other summary information...
}
 
void Game::findFood() 
{
    energyBar.minus(1);
}

void Game::findWater() 
{
    energyBar.minus(1);
}

void Game::explore()
{
    energyBar.minus(1);
}

void Game::rest() 
{
    energyBar.plus(1);
}

void Game::displayGameOver() const
{
    std::cout << "*********************************" << std::endl;
    // Display game over message
    std::cout << "Game Over! Thanks for playing." << std::endl;
}

void Game::displayLevelIntro() const
{
    std::cout << "*********************************" << std::endl;
    // Display level introduction message
    std::cout << "Welcome to the game! Level: " << levelFolder << std::endl;
}
