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
#include "Tram.h"


class Game
{
	Resources resources;
	sf::Window window;
	Camera mainCamera;
	Camera uiCamera;
	std::map<std::string, int> objectIds;
	std::vector<std::unique_ptr<GameObject>> objects;

	sf::Vector2i lastMousePos;

	Tram tram;

	sf::Clock clock;
	float totalTime;
	float deltaTime;

	bool isRunning;
	
public:
	void Start();
	void MainLoop();
	void Update();
	void Render();
	void Stop();

private:
	void OpenWindow();
	void InitializeObjects();

	void HandleEvent(sf::Event event);

	std::unique_ptr<GameObject>& AddObject(std::string name, std::string parentName, MeshId meshId, ShaderProgramId shaderId, TextureId textureId, Camera* camera);
	std::unique_ptr<GameObject>& GetObject(std::string name);
	void DrawObject(int objectId);
};
