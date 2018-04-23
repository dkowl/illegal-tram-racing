#include "Game.h"
#include "../Engine/UI/Sprite.h"
#include "Tram.h"
#include "../Engine/Components/MeshComponent.h"
#include "../Engine/Light/PbrLight.h"
#include "../Engine/Light/DirectionalLight.h"

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

ComponentContainer& Game::Components()
{
	return I().componentContainer;
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

void Game::LogError(std::string errorMessage)
{
	std::cout << "FATAL ERROR: " << errorMessage << std::endl;
	system("PAUSE");
}

void Game::Start()
{

	if (isRunning) return;

	OpenWindow();
	uiCamera.SetAspectRatio(AspectRatio());

	resources.Initialize();
	resources.MeshLayoutR::AddDynamic(std::make_unique<MeshLayout>(
		std::initializer_list<VertexAttribute>({
		VertexAttribute::POSITION,
		VertexAttribute::UV })
		),
		"MeshLayout1"
	);
	auto test = resources.MeshLayoutR::GetDynamic("MeshLayout1");
	std::cout << test->Size() << std::endl;
	system("PAUSE");

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

void Game::ApplyPbrLights()
{
	for(auto&& pbrLight : componentContainer.GetComponents<PbrLight>())
	{
		pbrLight->SetGlUniforms();
	}
}

void Game::Render()
{

	gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT);

	const unsigned int mainTextureLocation = gl::glGetUniformLocation(resources.Get(ShaderProgramId::MAIN)->GlId(), "mainTexture");
	gl::glUniform1i(mainTextureLocation, 0);

	ApplyPbrLights();

	for (auto& object : objects)
	{
		const auto meshComponent = object->GetComponent<MeshComponent>();
		if(meshComponent != nullptr)
		{
			meshComponent->Render();
		}
	}
	RenderSprites();
	
	window.display();
}

void Game::RenderSprites()
{
	for(auto&& sprite : componentContainer.GetComponents<Sprite>())
	{
		sprite->Render();
	}
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
	GameObject::BuildParams goParams;
	MeshComponent::BuildParams meshParams;
	//Tram
	goParams.name = "Tram";
	meshParams.meshId = MeshId::TRAM;
	meshParams.textureIds = { TextureId::TRAM };
	auto tramObject = AddObject<Tram>(goParams);
	tramObject->AddComponent<MeshComponent>(meshParams);
	tramObject->GetTransform().SetLocalScale(glm::vec3(0.05f));
	tramObject->Initialize();

	//Drone
	goParams.name = "Cabinet";
	meshParams.meshId = MeshId::CABINET;
	meshParams.textureIds = { 
		TextureId::CABINET_ALBEDO, 
		TextureId::CABINET_NORMAL,
		TextureId::CABINET_METALLIC,
	};
	meshParams.shaderId = ShaderProgramId::PBR;
	auto cabinetObject = AddObject<GameObject>(goParams);
	cabinetObject->AddComponent<MeshComponent>(meshParams);
	meshParams.shaderId = ShaderProgramId::MAIN;
	//cabinetObject->GetTransform().SetLocalScale(glm::vec3(50));
	cabinetObject->GetTransform().SetParent(&tramObject->GetTransform());
	cabinetObject->GetTransform().SetLocalPosition(glm::vec3(5, 0, -2));
	cabinetObject->GetTransform().Rotate(180, glm::vec3(0, 1, 0));

	//Track
	goParams.name = "Track";
	meshParams.meshId = MeshId::TRACK;
	meshParams.textureIds = { TextureId::TRACK };
	auto trackObject = AddObject<GameObject>(goParams);
	trackObject->AddComponent<MeshComponent>(meshParams);

	//Speedometer
	Sprite::BuildParams spriteP;
	goParams.name = "Speedometer";
	spriteP.textureId = TextureId::SPEEDOMETER;
	auto speedometer = AddObject<GameObject>(goParams);
	speedometer->GetTransform().SetLocalPosition(glm::vec3(1*AspectRatio()-0.4, -1+0.4, 0));
	speedometer->GetTransform().SetLocalScale(glm::vec3(0.33, 0.33, 1));
	spriteP.zDepth = 0.1;
	speedometer->AddComponent<Sprite>(spriteP);

	//Speedometer tip
	goParams.name = "Speedometer_tip";
	goParams.parentTransform = &speedometer->GetTransform();
	auto speedometerTip = AddObject<GameObject>(goParams);
	goParams.parentTransform = nullptr;
	spriteP.textureId = TextureId::SPEEDOMETER_TIP;
	spriteP.zDepth = 0.05;
	speedometerTip->AddComponent<Sprite>(spriteP);

	//Sun
	auto lightParams = DirectionalLight::MakeBuildParams(glm::vec3(1, -3, 1), glm::vec3(1), 10);
	goParams.name = "Sun";
	auto sunObject = AddObject<GameObject>(goParams);
	sunObject->AddComponent<PbrLight>(lightParams);

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


