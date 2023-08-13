#include <gtest/gtest.h>
#include <Core/Action.h>

TEST(ActionTest, MethodConstructorTest)
{
    // Test getting a random action
    Action action("data/levels/mtaspiring/actions.json");

    // Test getting a random action from a specific category
    QString randomAction = action.getAction("morale");  // Change "morale" to the desired category

    // Check if the returned action description is not empty
    ASSERT_TRUE(randomAction.isEmpty()) << "Random action is empty.";

    // Print the randomly selected action description
    std::cout << "Random action: " << randomAction.toStdString() << std::endl;
}