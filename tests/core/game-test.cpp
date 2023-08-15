#include <gtest/gtest.h>
#include <core/game.h>

TEST(GameTest, GameConstructorMethodTest)
{
	Game newGame("data/levels/mtaspiring");

	newGame.run();

}