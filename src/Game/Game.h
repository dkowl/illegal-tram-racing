#pragma once
#include <iostream>
#include <string>
#include <map>

#include "../glbinding.h"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Transform.h"
#include "../Resources/Resources.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Constants.h"
#include "../Engine/GameObject.h"
#include "../Utils.h"


class Game
{
	Resources resources;
	sf::Window window;
	std::map<std::string, int> objectIds;
	std::vector<std::unique_ptr<GameObject>> objects;
	
public:
	void Start();
	void MainLoop();
	void Update();
	void Render();

private:
	void AddObject(std::string name, std::string parentName, MeshId meshId);
	void DrawObject(int objectId);
};
