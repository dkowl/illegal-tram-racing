#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"



int main()
{
	glbinding::Binding::initialize(false);
	Game::I().Start();

	system("PAUSE");

	return 0;
}
