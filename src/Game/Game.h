#pragma once
#include <string>
#include <map>

#include "../glbinding.h"

#include <SFML/Window.hpp>

#include "../Engine/Transform.h"
#include "../Resources/Resources.h"
#include "../Engine/GameObject.h"
#include "../Engine/Camera/CameraPerspective.h"
#include "../Engine/Camera/CameraUi.h"


class Game
{
	static Game *instance;

	Resources resources;
	sf::VideoMode videoMode;
	sf::Window window;
	CameraPerspective mainCamera;
	CameraUi uiCamera;
	std::map<std::string, int> objectIds;
	std::vector<std::unique_ptr<GameObject>> objects;

	sf::Vector2i lastMousePos;

	sf::Clock clock;
	float totalTime;
	float deltaTime;

	bool isRunning;
	
public:
	static void Initialize();
	static Game& I();
	static const Resources& Resources();
	static float DeltaTime();
	static Camera* MainCamera();
	static float AspectRatio();

	void Start();
	void Stop();

	template <class T, class P>
	std::unique_ptr<GameObject>& AddObject(P &buildParams);
	std::unique_ptr<GameObject>& GetObject(std::string name);

private:
	Game();

	void MainLoop();
	void Update();
	void Render();

	void OpenWindow();
	void InitializeObjects();

	void HandleEvent(sf::Event event);
	void DrawObject(int objectId);

	void UpdateSpeedometer();

	Camera* GetCamera(CameraType type);
};
