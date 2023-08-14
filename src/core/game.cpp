#include <iostream>
#include <string>
#include <random>

#include "game.h"

Game::Game(const std::string& levelFolder) : levelFolder(levelFolder),
climate(levelFolder + "/climate.json"), // Initialize climate data
animal(convertQlevelFolder + "/animals.json"), // Initialize animal
plant(convertQlevelFolder + "/plants.json"), // Initialize Plant
disasters(convertQlevelFolder + "/disaster_ev.json"), // Initialize Disaster
energyBar(10),
hungerBar(10),
thirstBar(10),
healthBar(10)

{

    dayCounter = 1; // Start with Day 1
    turns = 5; // Initialize turns to 5
    alive = true; // Initialize player as alive
    move = true; // Initialize player to be able to move
    currentMonthIndex = 0; // Initialize monthindex to 1 (starts from january)

    // Temp fix
    maxTemperature = 10;
    avgTemperature = 10;
    minTemperature = 10;

    std::cout << "Game initialized for level: " << levelFolder << std::endl;
}

// Define the array of month names
const std::string Game::months[12] = 
{
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

// Run game
void Game::run()
{
    displayLevelIntro();

    while (alive)
    {

        std::cout << "Day: " << dayCounter << std::endl;
        std::cout << "Month: " << months[currentMonthIndex] << std::endl;
        std::cout << "Turns remaining: " << turns << std::endl;
        displayMainMenu();
        int choice = getMenuChoice();
        handleMenuChoice(choice);
        alive = isAlive();

        if (turns == 1) {
            std::cout << "Only 1 turn remaining!" << std::endl;
        }
        else if (turns == 0) {
            displayDaySummary();
            std::cout << "Day " << dayCounter << " ends!" << std::endl;
            // Update the current month and temperature when a new day begins
            updateMonth();
            updateTemperature();
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
    std::cout << "5. Display stats" << std::endl;
    std::cout << "6. Display temperature" << std::endl;
}

void Game::handleMenuChoice(int choice)
{
    if (choice == 6)
    {
        displayTemperature(); // display temps
        return;
    }

    if (choice == 5) {
        displayDaySummary(); // display stats for now
        return;
    }
    
    if (choice == 4) {
        rest();
        --turns; // Deduct a turn when a valid action is chosen
        return;
    }

    if (!canMove()) {
        std::cout << "You don't have enough energy to perform an action." << std::endl;
        return;
    }

    switch (choice) {
    case 1:
        findFood();
        --turns; // Deduct a turn when a valid action is chosen
        break;
    case 2:
        findWater();
        --turns; // Deduct a turn when a valid action is chosen
        break;
    case 3:
        explore();
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
    std::cout << "Health: " << healthBar.getValue() << "/ 10" << std::endl;
}
 
void Game::findFood() 
{
    energyBar.minus(1);

    // Set up a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    // Generate a random probability
    float probability = dist(gen);

    // 20% chance of finding nothing
    if (probability <= 0.2)
    {
        std::cout << "You found nothing while searching for food." << std::endl;
        return;
    }
    else
    {
        // Decide if it's an animal or a plant
        bool isAnimal = (dist(gen) <= 0.2); // 20% chance for animal

        if (isAnimal)
        {
            hungerBar.plus(3);
            std::cout << "You have found " << animal.getRandomAnimal("mammals").toStdString() << std::endl;
        }
        else
        {
            hungerBar.plus(1);
            QPair<QString, bool> randomPlant = plant.getRandomPlant("fungi");
            std::cout << "You have found " << randomPlant.first.toStdString() << std::endl;
            if (randomPlant.second == false)
            {
                std::cout << "That was not edible ew " << std::endl;
                healthBar.minus(3);
            }
            else
            {
                std::cout << "Ice cream so yum " << std::endl;
            }

        }
    }
}

void Game::findWater() 
{
    energyBar.minus(1);

    // Set up a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    // Generate a random probability
    float probability = dist(gen);

    if (probability <= 0.2) // 20 percent of finding nothing
    {
        std::cout << "Whoops found nothing " << std::endl;
    } 
    else
    {
        thirstBar.plus(2);
        bool cleanWater = (dist(gen) <= 0.6);
        if (cleanWater)
        {
            std::cout << "Clean water found " << std::endl;
        }
        else
        {
            healthBar.minus(2);
            std::cout << "Dirty water found " << std::endl;
        }
    }

}

void Game::explore()
{
    energyBar.minus(3);
    hungerBar.minus(2);
    thirstBar.minus(2);
    std::cout << "Something cool happens or something bad happens" << std::endl;
}

void Game::rest() 
{
    energyBar.plus(2);
    std::cout << "Ah yes good sleep" << std::endl;
    if (hungerBar.getValue() > 6 && thirstBar.getValue() > 6)
    {
        std::cout << "Wow you healed" << std::endl;
        healthBar.plus(3);
    }
}

bool Game::isAlive() const
{
    if (healthBar.getValue() == 0)
    {
        displayGameOver();
        return false;
    } 
    else
    {
        return true;
    }

}

bool Game::canMove() const
{
    if (energyBar.getValue() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Game::updateMonth()
{
    // Alternate months every 30 or 31 days
    if (dayCounter == 30) 
    {
        currentMonthIndex = (currentMonthIndex + 1) % 12;
        
    }
}

void Game::updateTemperature()
{
    // Get the current month data
    const std::vector<ClimateData>& currentMonthData = climate.getMonthData(months[currentMonthIndex]);

    // Iterate through the current month data
    for (const ClimateData& data : currentMonthData)
    {
        // Get random values for temperature fields and update them in your temperature variables
        float maxTemp = climate.getRandomTemperatureValue(data.max_temperature);
        float avgTemp = climate.getRandomTemperatureValue(data.avg_temperature);
        float minTemp = climate.getRandomTemperatureValue(data.min_temperature);

        // Update the temperature variables in your Game class
        this->maxTemperature = maxTemp;
        this->avgTemperature = avgTemp;
        this->minTemperature = minTemp;
    }
}

void Game::displayTemperature()
{
    std::cout << "Temperature for Day " << dayCounter << ":" << std::endl;
    std::cout << "Day/Evening Temp: " << avgTemperature << " °C" << std::endl;
    std::cout << "Afternoon Temp: " << maxTemperature << " °C" << std::endl;
    std::cout << "Night Temp: " << minTemperature << " °C" << std::endl;
}


void Game::displayGameOver() const
{
    std::cout << "*********************************" << std::endl;
    // Display game over message
    std::cout << "You died! Thanks for playing." << std::endl;
}

void Game::displayLevelIntro() const
{
    std::cout << "*********************************" << std::endl;
    // Display level introduction message
    std::cout << "Welcome to the game! Level: " << levelFolder << std::endl;
}
