#pragma warning(disable: 4251)

#include <iostream>

#include <glbinding/gl45core/gl.h>
#include <glbinding/Binding.h>

#include <SFML/Window.hpp>

#include "Resources.h"


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

	unsigned int vertexShader = gl::glCreateShader(gl::GLenum::GL_VERTEX_SHADER);
	const char* shaderSource = res.GetShader(ShaderId::MAIN_VERTEX_SHADER)->Source().c_str();
	gl::glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	gl::glCompileShader(vertexShader);
	std::cout << "Shader compiled successfully" << std::endl;
	system("PAUSE");

	return 0;
}
