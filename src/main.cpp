#include <iostream>

#include "glbinding.h"

#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Transform.h"
#include "Resources/Resources.h"
#include "Resources/Mesh/Mesh.h"
#include "Game/Game.h"


int main()
{
	glbinding::Binding::initialize(false);

	Game game;
	game.Start();

	/*sf::Window window(sf::VideoMode(800, 600), "Illegal Tram Racing");
	window.setActive(true);


	Resources res;

	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, //1.0f, 0.0f,

		0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	Mesh cube(vertices, indices);

	Transform transform;
	transform.Rotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
	transform.Scale(glm::vec3(0.5f, 0.5f, 1.0f));

	glm::mat4 modelMatrix = transform.ModelMatrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << modelMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}


	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	gl::glUseProgram(res.ShaderProgram());

	unsigned int transformLoc = gl::glGetUniformLocation(res.ShaderProgram(), "model");
	gl::glUniformMatrix4fv(transformLoc, 1, gl::GL_FALSE, glm::value_ptr(modelMatrix));

	gl::glBindVertexArray(cube.Vao()); 
	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, gl::GLenum::GL_LINE);
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, 36, gl::GLenum::GL_UNSIGNED_INT, nullptr);

	window.display();*/
	return 0;
}
