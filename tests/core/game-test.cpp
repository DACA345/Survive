#include <gtest/gtest.h>
#include <core/game.h>

TEST(GAMEPLAYTEST, GameConstructorMethodTest)
{
	Game newGame("data/levels/mtaspiring");

	newGame.run();
}