#include "Game.h"

void Game::Start()
{
	window.create(
		sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
		Constants::CurrentText().GetText(LocalizedText::TextType::WINDOW_TITLE)
		);
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
