#pragma once
#include <string>
#include <vector>

#include <SFML/System.hpp>

class LocalizedText
{
public:
	enum class TextType
	{
		WINDOW_TITLE
	};

private:
	std::vector<sf::String> text;

public:
	LocalizedText(std::vector<sf::String> &&text);
	const sf::String& GetText(TextType type) const;
};
