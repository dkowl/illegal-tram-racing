#include "Game.h"

void Game::Start()
{
	window.create(
		sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
		Constants::CurrentText().GetText(LocalizedText::TextType::WINDOW_TITLE)
		);
	window.setActive(true);

	resources.Initialize();

	AddObject("Cube", "", MeshId::CUBE);

	MainLoop();
}

void Game::MainLoop()
{

	bool running = true;
	while(running)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if(event.type == sf::Event::Resized)
			{
				gl::glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		Render();
	}
	window.close();
}

void Game::Update()
{
}

void Game::Render()
{
	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	gl::glUseProgram(resources.ShaderProgram());
	for (int i = 0; i < objects.size(); i++)
	{
		DrawObject(i);
	}
	window.display();
}

void Game::AddObject(std::string name, std::string parentName, MeshId meshId)
{
	Transform* parentTransform = nullptr;
	if(objectIds.find(parentName) != objectIds.end())
	{
		parentTransform = objects[objectIds[parentName]]->GetTransform();
	}
	objects.push_back(std::make_unique<GameObject>(name, parentTransform, meshId));
	objectIds[name] = objects.size() - 1;
}

void Game::DrawObject(int objectId)
{
	unsigned int modelLocation = gl::glGetUniformLocation(resources.ShaderProgram(), "model");
	glm::mat4 modelMatrix = objects[objectId]->GetTransform()->ModelMatrix();
	//Utils::DisplayMat4(modelMatrix);
	gl::glUniformMatrix4fv(modelLocation, 1, gl::GL_FALSE, glm::value_ptr(modelMatrix));

	auto& mesh = resources.GetMesh(objects[objectId]->GetMeshId());
	gl::glBindVertexArray(mesh->Vao());
	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, gl::GLenum::GL_LINE);
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, mesh->ElementCount(), gl::GLenum::GL_UNSIGNED_INT, nullptr);
}
