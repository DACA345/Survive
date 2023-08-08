#include <gtest/gtest.h>
#include <Core/Plant.h>

TEST(PlantTest, MethodConstructorTest)
{
    Plant testPlant("C:/Users/Andrew John/Source/Repos/DACA345/Survive/tests/data/levels/mtaspiring/plants.json");

    // Test for the "Fungi" category
    QPair<QString, bool> randomFungus = testPlant.getRandomPlant("fungi");
    ASSERT_FALSE(randomFungus.first.isEmpty());
    std::cout << "Random Fungus: " << randomFungus.first.toStdString()
        << ", Edible: " << (randomFungus.second ? "true" : "false") << std::endl;

    // Test for the "Plant" category
    QPair<QString, bool> randomPlant = testPlant.getRandomPlant("plant");
    ASSERT_FALSE(randomPlant.first.isEmpty());
    std::cout << "Random Plant: " << randomPlant.first.toStdString()
        << ", Edible: " << (randomPlant.second ? "true" : "false") << std::endl;
}