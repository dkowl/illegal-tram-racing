#include "Game.h"

void Game::Start()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.antialiasingLevel = 4;

	const auto& videoModes = sf::VideoMode::getFullscreenModes();
	int bestIndex = 0;
	int maxPixels = 0;
	for (int i = 0; i < videoModes.size(); i++)
	{
		int pixels = videoModes[i].width * videoModes[i].height * videoModes[i].bitsPerPixel;
		if(pixels > maxPixels)
		{
			maxPixels = pixels;
			bestIndex = i;
		}
	}
	window.create(
		videoModes[bestIndex],
		Constants::CurrentText().GetText(LocalizedText::TextType::WINDOW_TITLE),
		sf::Style::Fullscreen,
		settings
		);
	window.setActive(true);

	resources.Initialize();

	gl::glEnable(gl::GLenum::GL_DEPTH_TEST);
	
	auto& tram = AddObject("Tram", "", MeshId::TRAM, ShaderProgramId::MAIN, TextureId::TRAM);
	tram->GetTransform().SetLocalScale(glm::vec3(0.05f));

	//auto& tram2 = AddObject("Tram2", "", MeshId::TRAM, ShaderProgramId::MAIN, TextureId::CRATE);
	//tram2->GetTransform().SetLocalScale(glm::vec3(0.01f));

	auto& track = AddObject("Track", "", MeshId::TRACK, ShaderProgramId::MAIN, TextureId::TRACK);
	//track->SetPolygonMode(GameObject::PolygonMode::LINE);

	MainLoop();
}

void Game::MainLoop()
{
	clock.restart();
	bool running = true;
	while(running)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				running = false;
			}
			else if(event.type == sf::Event::Resized)
			{
				gl::glViewport(0, 0, event.size.width, event.size.height);
			}
			else if(event.type == sf::Event::MouseWheelScrolled)
			{
				camera.Zoom(event.mouseWheelScroll.delta * -1.0f * Constants::MOUSE_WHEEL_ZOOM_SPEED);
			}
		}

		Update();
		Render();
	}
	window.close();
}

void Game::Update()
{
	sf::Vector2i mouseOffset = sf::Mouse::getPosition() - lastMousePos;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (mouseOffset.x != 0 || mouseOffset.y != 0))
	{
		camera.RotateAround(mouseOffset.x, mouseOffset.y);
	}
	lastMousePos = sf::Mouse::getPosition();

	tram.Update(deltaTime);

	auto& track = resources.GetTrack();
	auto& tramObject = GetObject("Tram");
	auto tramAxisPositions = track->GetTramAxisPositions(tram.DistanceTraveled(), Tram::AXIS_DISTANCE);
	glm::vec3 tramPosition = glm::mix(tramAxisPositions[0], tramAxisPositions[1], 0.5f);
	float tramYRotation = glm::degrees(Utils::GetYRotation(tramAxisPositions[0] - tramAxisPositions[1]));
	std::cout << "tram Y rotation: " << tramYRotation << std::endl;
	tramObject->GetTransform().SetLocalPosition(tramPosition);
	tramObject->GetTransform().SetLocalRotation(180 - tramYRotation, glm::vec3(0, 1, 0));
	camera.SetYaw(-tramYRotation);
	camera.SetTarget(tramObject->GetTransform().Position());

	deltaTime = clock.getElapsedTime().asSeconds();
	totalTime += deltaTime;
	clock.restart();
}

void Game::Render()
{

	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	const unsigned int mainTextureLocation = gl::glGetUniformLocation(resources.GetShaderProgram(ShaderProgramId::MAIN)->GlId(), "mainTexture");
	gl::glUniform1i(mainTextureLocation, 0);

	for (int i = 0; i < objects.size(); i++)
	{
		DrawObject(i);
	}
	window.display();
}

std::unique_ptr<GameObject>& Game::AddObject(std::string name, std::string parentName, MeshId meshId, ShaderProgramId shaderId, TextureId textureId)
{
	Transform* parentTransform = nullptr;
	if(objectIds.find(parentName) != objectIds.end())
	{
		parentTransform = &objects[objectIds[parentName]]->GetTransform();
	}
	objects.push_back(std::make_unique<GameObject>(name, parentTransform, meshId, shaderId, textureId));
	objectIds[name] = objects.size() - 1;
	return objects.back();
}

std::unique_ptr<GameObject>& Game::GetObject(std::string name)
{
	if(objectIds.find(name) == objectIds.end())
	{
		std::cout << "Object " << name << " not found";
		return objects[0];
	}
	return objects[objectIds[name]];
}

void Game::DrawObject(int objectId)
{
	const auto& object = objects[objectId];
	const auto& shaderProgram = resources.GetShaderProgram(object->GetShaderId())->GlId();
	const auto& texture = resources.GetTexture(object->GetTextureId())->GlId();
	const auto& mesh = resources.GetMesh(object->GetMeshId());

	//shader
	gl::glUseProgram(shaderProgram);

	const unsigned int modelLocation = gl::glGetUniformLocation(shaderProgram, "model");
	gl::glUniformMatrix4fv(modelLocation, 1, gl::GL_FALSE, glm::value_ptr(object->GetTransform().ModelMatrix()));

	const unsigned int viewLocation = gl::glGetUniformLocation(resources.GetShaderProgram(ShaderProgramId::MAIN)->GlId(), "view");
	gl::glUniformMatrix4fv(viewLocation, 1, gl::GL_FALSE, glm::value_ptr(camera.ViewMatrix()));

	const unsigned int projectionLocation = gl::glGetUniformLocation(resources.GetShaderProgram(ShaderProgramId::MAIN)->GlId(), "projection");
	gl::glUniformMatrix4fv(projectionLocation, 1, gl::GL_FALSE, glm::value_ptr(camera.ProjectionMatrix()));

	//texture
	gl::glActiveTexture(gl::GLenum::GL_TEXTURE0);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, texture);

	//mesh
	gl::glBindVertexArray(mesh->Vao());

	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, object->GetPolygonMode());
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, mesh->ElementCount(), gl::GLenum::GL_UNSIGNED_INT, nullptr);
}
