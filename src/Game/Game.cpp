#include "Game.h"

Game* Game::instance = nullptr;

void Game::Initialize()
{
	instance = new Game();
}

Game& Game::I()
{
	if (instance == nullptr) Initialize();
	return *instance;
}

void Game::Start()
{
	if (isRunning) return;

	OpenWindow();

	resources.Initialize();

	InitializeObjects();

	gl::glEnable(gl::GLenum::GL_DEPTH_TEST);

	clock.restart();
	totalTime = 0;
	deltaTime = 0;
	isRunning = true;
	
	MainLoop();
}

void Game::MainLoop()
{
	while(isRunning)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			HandleEvent(event);
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
		mainCamera.RotateAround(mouseOffset.x, mouseOffset.y);
	}
	lastMousePos = sf::Mouse::getPosition();

	tram.Update(deltaTime);

	auto& track = resources.GetTrack();
	auto& tramObject = GetObject("Tram");
	auto tramAxisPositions = track->GetTramAxisPositions(tram.DistanceTraveled(), Tram::AXIS_DISTANCE);
	const glm::vec3 tramPosition = glm::mix(tramAxisPositions[0], tramAxisPositions[1], 0.5f);
	const float tramYRotation = glm::degrees(Utils::GetYRotation(tramAxisPositions[0] - tramAxisPositions[1]));
	tramObject->GetTransform().SetLocalPosition(tramPosition);
	tramObject->GetTransform().SetLocalRotation(180 - tramYRotation, glm::vec3(0, 1, 0));
	mainCamera.SetYaw(-tramYRotation);
	mainCamera.SetTarget(tramObject->GetTransform().Position());

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

void Game::Stop()
{
	isRunning = false;
}

Game::Game():
	isRunning(false)
{
}

void Game::OpenWindow()
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
		if (pixels > maxPixels)
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
}

void Game::InitializeObjects()
{
	auto& tram = AddObject("Tram", "", MeshId::TRAM, ShaderProgramId::MAIN, TextureId::TRAM, &mainCamera);
	tram->GetTransform().SetLocalScale(glm::vec3(0.05f));

	auto& track = AddObject("Track", "", MeshId::TRACK, ShaderProgramId::MAIN, TextureId::TRACK, &mainCamera);
}

void Game::HandleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
	{
		Stop();
	}
	else if (event.type == sf::Event::Resized)
	{
		gl::glViewport(0, 0, event.size.width, event.size.height);
	}
	else if (event.type == sf::Event::MouseWheelScrolled)
	{
		mainCamera.Zoom(event.mouseWheelScroll.delta * -1.0f * Constants::MOUSE_WHEEL_ZOOM_SPEED);
	}
}

std::unique_ptr<GameObject>& Game::AddObject(std::string name, std::string parentName, MeshId meshId, ShaderProgramId shaderId, TextureId textureId, Camera* camera)
{
	Transform* parentTransform = nullptr;
	if(objectIds.find(parentName) != objectIds.end())
	{
		parentTransform = &objects[objectIds[parentName]]->GetTransform();
	}
	objects.push_back(std::make_unique<GameObject>(name, parentTransform, meshId, shaderId, textureId, camera));
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
	gl::glUniformMatrix4fv(viewLocation, 1, gl::GL_FALSE, glm::value_ptr(object->GetCamera()->ViewMatrix()));

	const unsigned int projectionLocation = gl::glGetUniformLocation(resources.GetShaderProgram(ShaderProgramId::MAIN)->GlId(), "projection");
	gl::glUniformMatrix4fv(projectionLocation, 1, gl::GL_FALSE, glm::value_ptr(object->GetCamera()->ProjectionMatrix()));

	//texture
	gl::glActiveTexture(gl::GLenum::GL_TEXTURE0);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, texture);

	//mesh
	gl::glBindVertexArray(mesh->Vao());

	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, object->GetPolygonMode());
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, mesh->ElementCount(), gl::GLenum::GL_UNSIGNED_INT, nullptr);
}


