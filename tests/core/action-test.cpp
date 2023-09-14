#include <gtest/gtest.h>
#include <core/action.h>

TEST(ActionTest, MethodConstructorTest)
{
    Action testAction("data/levels/mtaspiring/action.json");

    // Test for the "Fungi" category
    EXPECT_NO_THROW(testAction.getRandomActionCategory());
    EXPECT_NO_THROW(testAction.getRandomAction());
    EXPECT_NO_THROW(testAction.getRandomActionInCategory("morale"));

    ASSERT_FALSE(testAction.getRandomAction().actionsID == "");
    ASSERT_FALSE(testAction.getRandomAction().category == "");
}
