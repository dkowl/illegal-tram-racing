#include <iostream>

#include "glbinding.h"

#include <SFML/Window.hpp>

#include "Resources/Resources.h"


int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Illegal Tram Racing");
	window.setActive(true);

	glbinding::Binding::initialize(false);

	Resources res;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int vbo;
	gl::glGenBuffers(1, &vbo);
	unsigned int vao;
	gl::glGenVertexArrays(1, &vao);

	gl::glBindVertexArray(vao);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, vbo);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(vertices), vertices, gl::GLenum::GL_STATIC_DRAW);
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 3 * sizeof(float), nullptr);
	gl::glEnableVertexAttribArray(0);

	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	gl::glUseProgram(res.ShaderProgram());
	gl::glBindVertexArray(vao);
	gl::glDrawArrays(gl::GLenum::GL_TRIANGLES, 0, 3);

	window.display();
	
	system("PAUSE");

	return 0;
}
