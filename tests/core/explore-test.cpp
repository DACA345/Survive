#include <gtest/gtest.h>
#include <core/explore.h>

TEST(ExploreTest, MethodConstructorTest)
{
    // Test getting a random action
    Explore explore("data/levels/mtaspiring/explore_event.json");

    // Test getting a random action from a specific category
    QString randomAction = explore.getRandomExplores("Encounter");  // Change "morale" to the desired category

    // Print the randomly selected action description
    std::cout << "Random Encounter: You encountered " << randomAction.toStdString() << std::endl;
}