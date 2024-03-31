#include <iostream>
#include "Game/Game.h"
#include <sol/sol.hpp>

int main()
{
    Game game;
    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}