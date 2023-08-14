#include <gtest/gtest.h>
#include <Core/Bar.h>

TEST(BarTest, MethodTest)
{
    Bar energyBar(10); // Create a Bar instance with initial value 10

    // Print initial value
    std::cout << "Initial value: " << energyBar.getValue() << std::endl;

    // Call minus method
    energyBar.minus(1);

    // Print value after minus(1)
    std::cout << "Value after minus(1): " << energyBar.getValue() << std::endl;

    // Check value after minus(1)
    EXPECT_EQ(energyBar.getValue(), 9);
}