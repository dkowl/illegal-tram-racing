#include "Game.h"
#include "../Engine/UI/Sprite.h"
#include "Tram.h"

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

const Resources& Game::Resources()
{
	return I().resources;
}

float Game::DeltaTime()
{
	return I().deltaTime;
}

Camera* Game::MainCamera()
{
	return &I().mainCamera;
}

float Game::AspectRatio()
{
	return float(I().videoMode.width) / I().videoMode.height;
}

void Game::Start()
{

	if (isRunning) return;

	OpenWindow();
	uiCamera.SetAspectRatio(AspectRatio());

	resources.Initialize();

	InitializeObjects();
	screenshake.Initialize();

	gl::glEnable(gl::GLenum::GL_DEPTH_TEST);
	gl::glEnable(gl::GLenum::GL_BLEND);
	gl::glBlendFunc(gl::GLenum::GL_SRC_ALPHA, gl::GLenum::GL_ONE_MINUS_SRC_ALPHA);

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
	for(auto&& object: objects)
	{
		object->Update();
	}

	UpdateSpeedometer();
	mainCamera.Update();
	//screenshake.Update();
	
	sf::Vector2i mouseOffset = sf::Mouse::getPosition() - lastMousePos;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (mouseOffset.x != 0 || mouseOffset.y != 0))
	{
		mainCamera.RotateAround(mouseOffset.x, mouseOffset.y);
	}
	lastMousePos = sf::Mouse::getPosition();	

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
	videoMode = videoModes[bestIndex];
	window.create(
		videoMode,
		Constants::CurrentText().GetText(LocalizedText::TextType::WINDOW_TITLE),
		sf::Style::Fullscreen,
		settings
		);
	window.setActive(true);
}

void Game::InitializeObjects()
{
	GameObject::BuildParams p;
	//Tram
	p.name = "Tram";
	p.meshId = MeshId::TRAM;
	p.textureId = TextureId::TRAM;
	auto tramObject = AddObject<Tram>(p);
	tramObject->GetTransform().SetLocalScale(glm::vec3(0.05f));
	tramObject->Initialize();

	//Track
	p.name = "Track";
	p.meshId = MeshId::TRACK;
	p.textureId = TextureId::TRACK;
	auto trackObject = AddObject<GameObject>(p);

	//Speedometer
	Sprite::BuildParams spriteP;
	spriteP.name = "Speedometer";
	spriteP.textureId = TextureId::SPEEDOMETER;
	auto speedometer = AddObject<Sprite>(spriteP);
	speedometer->GetTransform().SetLocalPosition(glm::vec3(1*AspectRatio()-0.4, -1+0.4, 0));
	speedometer->GetTransform().SetLocalScale(glm::vec3(0.33, 0.33, 1));
	spriteP.zDepth = 0.1;

	//Speedometer tip
	spriteP.name = "Speedometer_tip";
	spriteP.parentTransform = &speedometer->GetTransform();
	spriteP.textureId = TextureId::SPEEDOMETER_TIP;
	spriteP.zDepth = 0.05;
	AddObject<Sprite>(spriteP);
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
	gl::glUniformMatrix4fv(viewLocation, 1, gl::GL_FALSE, glm::value_ptr(GetCamera(object->Camera())->ViewMatrix()));

	const unsigned int projectionLocation = gl::glGetUniformLocation(resources.GetShaderProgram(ShaderProgramId::MAIN)->GlId(), "projection");
	gl::glUniformMatrix4fv(projectionLocation, 1, gl::GL_FALSE, glm::value_ptr(GetCamera(object->Camera())->ProjectionMatrix()));

	//texture
	gl::glActiveTexture(gl::GLenum::GL_TEXTURE0);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, texture);

	//mesh
	gl::glBindVertexArray(mesh->Vao());

	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, object->GetPolygonMode());
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, mesh->ElementCount(), gl::GLenum::GL_UNSIGNED_INT, nullptr);
}

void Game::UpdateSpeedometer()
{
	auto& speedometerTip = GetObject("Speedometer_tip");
	auto& tram = dynamic_cast<Tram&>(*GetObject("Tram"));

	speedometerTip->GetTransform().SetLocalRotation(246 * 3.6 * tram.Speed() / 90, glm::vec3(0, 0, -1));
}

Camera* Game::GetCamera(CameraType type)
{
	switch(type)
	{
	case CameraType::MAIN:
		return &mainCamera;
	case CameraType::UI:
		return &uiCamera;
	default:
		return &mainCamera;
	}
}


