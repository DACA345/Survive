#include <core/game.h>

int main(int argc, char** argv)
{
    Game newGame("data/levels/mtaspiring");
    newGame.run();
    
    return 0;
}