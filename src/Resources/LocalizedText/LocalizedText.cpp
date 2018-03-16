#include "LocalizedText.h"

LocalizedText::LocalizedText(std::vector<sf::String> &&text)
{
	this->text = std::move(text);
}

const sf::String& LocalizedText::GetText(TextType type) const
{
	return text[int(type)];
}
