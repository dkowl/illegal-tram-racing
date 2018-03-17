#include <iostream>

#include "glbinding.h"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Transform.h"
#include "Resources/Resources.h"
#include "Resources/Mesh/Mesh.h"
#include "Game/Game.h"


int main()
{
	glbinding::Binding::initialize(false);

	Game game;
	game.Start();

	return 0;
}
