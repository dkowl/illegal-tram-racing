#include "Game.h"

void Game::Start()
{
	window.create(
		sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
		Constants::CurrentText().GetText(LocalizedText::TextType::WINDOW_TITLE)
		);

	AddObject("Cube", "", MeshId::CUBE);
}

void Game::MainLoop()
{
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::AddObject(std::string name, std::string parentName, MeshId meshId)
{
	Transform* parentTransform = nullptr;
	if(objects.find(parentName) != objects.end())
	{
		parentTransform = objects[parentName]->GetTransform();
	}
	auto object = std::make_unique<GameObject>(name, parentTransform, meshId);
}
