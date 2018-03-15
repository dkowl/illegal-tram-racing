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

	//vertex shader
	unsigned int vertexShader = gl::glCreateShader(gl::GLenum::GL_VERTEX_SHADER);
	const char* shaderSource = res.GetShader(ShaderId::MAIN_VERTEX)->Source().c_str();
	gl::glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	gl::glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	gl::glGetShaderiv(vertexShader, gl::GLenum::GL_COMPILE_STATUS, &success);
	if (!success)
	{
		gl::glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::MAIN_VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader compiled successfully" << std::endl;

	//fragment shader
	unsigned int fragmentShader = gl::glCreateShader(gl::GLenum::GL_FRAGMENT_SHADER);
	shaderSource = res.GetShader(ShaderId::MAIN_FRAGMENT)->Source().c_str();
	gl::glShaderSource(fragmentShader, 1, &shaderSource, nullptr);
	gl::glCompileShader(fragmentShader);

	gl::glGetShaderiv(fragmentShader, gl::GLenum::GL_COMPILE_STATUS, &success);
	if (!success)
	{
		gl::glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::MAIN_FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader compiled successfully" << std::endl;


	system("PAUSE");

	return 0;
}
