#include <iostream>

#include "Game.h"
#include "Config.h"



int main()
{
	Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "cc");
	game.run();
}
