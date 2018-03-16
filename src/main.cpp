#include <iostream>

#include "glbinding.h"

#include <SFML/Window.hpp>

#include "Resources/Resources.h"
#include "Resources/Mesh/Mesh.h"


int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Illegal Tram Racing");
	window.setActive(true);

	glbinding::Binding::initialize(false);

	Resources res;

	std::vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	std::vector<unsigned int> indices = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Mesh rectangle(vertices, indices);

	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	gl::glUseProgram(res.ShaderProgram());
	gl::glBindVertexArray(rectangle.Vao());
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, 6, gl::GLenum::GL_UNSIGNED_INT, nullptr);

	window.display();
	
	system("PAUSE");

	return 0;
}
