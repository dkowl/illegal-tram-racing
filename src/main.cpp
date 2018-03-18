#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"




int main()
{
	glbinding::Binding::initialize(false);
	Game game;
	game.Start();

	return 0;
}
