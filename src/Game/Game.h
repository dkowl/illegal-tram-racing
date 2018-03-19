#pragma once
#include <iostream>
#include <string>
#include <map>

#include "../glbinding.h"

#include <SFML/Window.hpp>

#include "../Engine/Transform.h"
#include "../Resources/Resources.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Constants.h"
#include "../Engine/GameObject.h"
#include "../Utils.h"
#include "../Engine/Camera.h"


class Game
{
	Resources resources;
	sf::Window window;
	Camera camera;
	std::map<std::string, int> objectIds;
	std::vector<std::unique_ptr<GameObject>> objects;

	sf::Vector2i lastMousePos;
	
public:
	void Start();
	void MainLoop();
	void Update();
	void Render();

private:
	std::unique_ptr<GameObject>& AddObject(std::string name, std::string parentName, MeshId meshId, ShaderProgramId shaderId, TextureId textureId);
	void DrawObject(int objectId);
};
