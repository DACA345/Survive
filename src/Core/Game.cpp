#include "Game.h"
#include <iostream>
#include <string>

Game::Game(const std::string& levelFolder) : levelFolder(levelFolder),
climate(levelFolder + "/climate.json"), // Initialize climate data
animal(convertQlevelFolder + "/animals.json"), // Initialize animal
plant(convertQlevelFolder + "/plants.json"), // Initialize Plant
disasters(convertQlevelFolder + "/disaster_ev.json") // Initialize Disaster

{
    // Initialize your game here, based on the chosen level
    // Load data from the appropriate folder (e.g., "levels/mtaspiring")

    // Initialize Bar
    Bar energyBar(10);
    Bar hungerBar(10);
    Bar thirstBar(10);


    // You can also print a message to indicate that the game is initialized
    std::cout << "Game initialized for level: " << levelFolder << std::endl;
}


void Game::run()
{
    displayLevelIntro();

    while (true) {
        displayMainMenu();
        int choice = getMenuChoice();
        handleMenuChoice(choice);
    }
}

int Game::getMenuChoice() const
{
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

void Game::handleMenuChoice(int choice)
{
    switch (choice) {
    case 1:
        // Handle actions menu
        displayActionsMenu();
        break;
    case 2:
        // Handle events
        displayEvents();
        break;
    case 3:
        // Handle day summary
        displayDaySummary();
        break;
    case 4:
        // Handle game over
        displayGameOver();
        break;
    default:
        std::cout << "Invalid choice. Please select a valid option." << std::endl;
    }
}

void Game::displayMainMenu() const
{
    // Display the main menu options
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. Perform Actions" << std::endl;
    std::cout << "2. View Events" << std::endl;
    std::cout << "3. Display Day Summary" << std::endl;
    std::cout << "4. Game Over" << std::endl;
}

void Game::displayDaySummary() const
{
    // Display the summary for the day
    std::cout << "Day Summary:" << std::endl;
    // Display energy, hunger, thirst bars
    std::cout << "Energy: " << energyBar.getValue() << "/ 10" << std::endl;
    std::cout << "Hunger: " << hungerBar.getValue() << "/ 10" << std::endl;
    std::cout << "Thirst: " << thirstBar.getValue() << "/ 10" << std::endl;
    // Display other summary information...
}

void Game::displayGameOver() const
{
    // Display game over message
    std::cout << "Game Over! Thanks for playing." << std::endl;
}

void Game::displayLevelIntro() const
{
    // Display level introduction message
    std::cout << "Welcome to the game! Level: " << levelFolder << std::endl;
}

void Game::displayActionsMenu() const
{
    // Display actions menu options
    std::cout << "Actions Menu:" << std::endl;
    // Display actions options...
}

void Game::displayEvents() const
{
    // Display current events in the game
    std::cout << "Current Events:" << std::endl;
    // Display event information...
}
