#include <gtest/gtest.h>
#include <core/plant.h>

TEST(PlantTest, ValueTests)
{
    Plant testPlant("data/levels/mtaspiring/plants.json");

    // Test for the "Fungi" category
    EXPECT_NO_THROW(testPlant.getRandomPlantCategory());
    EXPECT_NO_THROW(testPlant.getRandomPlant());
    EXPECT_NO_THROW(testPlant.getRandomPlantInCategory("fungi"));
    EXPECT_NO_THROW(testPlant.getRandomPlantInCategory("plant"));

    Plant emptyPlant("data/levels/mtaspiring/empty.json");
    Plant nonexistPlant("data/levels/mtaspiring/nonExist.json");

    ASSERT_FALSE(testPlant.getRandomPlant().name == "");
    ASSERT_FALSE(testPlant.getRandomPlant().category == "");
    
}