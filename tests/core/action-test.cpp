#include <gtest/gtest.h>
#include <core/action.h>

TEST(ActionTest, MethodConstructorTest)
{
    // Test getting a random action
    Action action("data/levels/mtaspiring/actions.json");

    // Test getting a random action from a specific category
    QString randomAction = action.getRandomAction("morale");  // Change "morale" to the desired category

    // Print the randomly selected action description
    std::cout << "Random action: " << randomAction.toStdString() << std::endl;
}