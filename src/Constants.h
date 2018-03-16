#pragma once
#include <string>
#include "Resources/LocalizedText/LocalizedText.h"

namespace Constants
{
	enum class Language
	{
		EN,
		PL
	};

	extern const std::string RESOURCE_PATH;

	extern const int SCREEN_WIDTH;
	extern const int SCREEN_HEIGHT;
	extern const Language LANGUAGE;
	extern const LocalizedText TEXT_EN;
	extern const LocalizedText TEXT_PL;
	const LocalizedText& CurrentText();
	
}

