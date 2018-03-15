#include <iostream>

#include "glbinding.h"

#include <SFML/Window.hpp>

#include "Resources/Resources.h"


int main()
{
	glbinding::Binding::initialize(false);

	sf::Window window(sf::VideoMode(600, 800), "Illegal Tram Racing");

	Resources res;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int vbo;
	gl::glGenBuffers(1, &vbo);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, vbo);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(vertices), vertices, gl::GLenum::GL_STATIC_DRAW);
	
	system("PAUSE");

	return 0;
}
