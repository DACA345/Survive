#include <gtest/gtest.h>
#include <Core/Game.h>

TEST(GAMEPLAYTEST, GameConstructorMethodTest)
{
	Game newGame("data/levels/mtaspiring");

	newGame.run();
}