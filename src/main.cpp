#include <iostream>

#include "glbinding.h"

#include "Game/Game.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



int main()
{
	glbinding::Binding::initialize(false);

	Assimp::Importer importer;

	Game game;
	game.Start();

	return 0;
}
