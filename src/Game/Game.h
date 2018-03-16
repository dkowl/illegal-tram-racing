#pragma once
#include <iostream>
#include <string>

#include "../glbinding.h"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Transform.h"
#include "../Resources/Resources.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Constants.h"


class Game
{
	sf::Window window;
	Resources resources;
	
public:
	void Start();
	void MainLoop();
	void Update();
	void Render();
};