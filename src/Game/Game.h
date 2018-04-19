#pragma once
#include <string>
#include <map>

#include "../glbinding.h"

#include <SFML/Window.hpp>

#include "../Engine/Transform.h"
#include "../Resources/Resources.h"
#include "CameraType.h"
#include "../Engine/Camera/CameraPerspective.h"
#include "../Engine/Camera/CameraUi.h"
#include "../Engine/Camera/Screenshake.h"
#include "../Engine/ComponentContainer.h"

class GameObject;

class Game
{
	static Game *instance;

	Resources resources;
	ComponentContainer componentContainer;
	sf::VideoMode videoMode;
	sf::Window window;
	CameraPerspective mainCamera;
	CameraUi uiCamera;
	Screenshake screenshake;
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
	static ComponentContainer& Components();
	static float DeltaTime();
	static Camera* MainCamera();
	static float AspectRatio();
	static void LogError(std::string errorMessage);

	void Start();
	void Stop();

	template <class T, class P>	T* AddObject(P &buildParams);
	std::unique_ptr<GameObject>& GetObject(std::string name);
	template<typename T> T* GetObject(std::string name);
	Camera* GetCamera(CameraType type);

private:
	Game();

	void MainLoop();

	void Update();

	void ApplyPbrLights();
	void Render();


	void OpenWindow();
	void InitializeObjects();

	void HandleEvent(sf::Event event);
	void DrawObject(int objectId);

	void UpdateSpeedometer();

};

template <class T, class P>
T* Game::AddObject(P &buildParams)
{
	objects.push_back(std::make_unique<T>(buildParams));
	objectIds[buildParams.name] = objects.size() - 1;
	return static_cast<T*>(objects.back().get());
}

template <class T>
T* Game::GetObject(std::string name)
{
	auto& object = GetObject(name);
	return static_cast<T*>(object.get());
}
