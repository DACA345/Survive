#include <gtest/gtest.h>
#include <core/animal.h>

TEST(AnimalTest, MethodConstructorTest)
{
    Animal testAnimal("data/levels/mtaspiring/animals.json");

    // Test for the "birds" category
    EXPECT_NO_THROW(testAnimal.getRandomAnimalCategory());
    EXPECT_NO_THROW(testAnimal.getRandomAnimal());
    EXPECT_NO_THROW(testAnimal.getRandomAnimalInCategory("birds"));
    EXPECT_NO_THROW(testAnimal.getRandomAnimalInCategory("mammals"));

    ASSERT_FALSE(testAnimal.getRandomAnimal().name == "");
    ASSERT_FALSE(testAnimal.getRandomAnimal().category == "");

}