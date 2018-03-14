#pragma warning(disable: 4251)

#include <glbinding/gl45core/gl.h>
#include <glbinding/Binding.h>

#include <SFML/Window.hpp>


int main()
{
	glbinding::Binding::initialize(false);

	sf::Window window(sf::VideoMode(600, 800), "Illegal Tram Racing");


	return 0;
}