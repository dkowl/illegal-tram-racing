#include "Constants.h"

namespace Constants
{
	const std::string RESOURCE_PATH = "res/";

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	float AspectRatio()
	{
		return float(SCREEN_WIDTH) / SCREEN_HEIGHT;
	}
	const Language LANGUAGE = Language::PL;
	const LocalizedText TEXT_EN(std::vector<sf::String>{
		L"Illegal Tram Racing"
	});
	const LocalizedText TEXT_PL(std::vector<sf::String>{
		L"Nielegalne Wyœcigi Tramwajów"
	});
	const LocalizedText& CurrentText()
	{
		switch(LANGUAGE)
		{
		case Language::EN:
			return TEXT_EN;
		case Language::PL:
			return TEXT_PL;
		}
	}
	extern const float MOUSE_WHEEL_ZOOM_SPEED = 0.1f;
}
