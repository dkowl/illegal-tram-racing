#include "Tram.h"
#include "Game.h"

const float Tram::ACCELERATION = 5;
const float Tram::MAX_SPEED = 50;
const float Tram::BRAKING_DECELERATION = 8;
const float Tram::STATIC_FRICTION_DECELERATION = 3;
const float Tram::FRICTION_DECELERATION = 2;
const float Tram::AXIS_DISTANCE = 8;
const float Tram::SPEED_MULTIPLIER = 10;


Tram::Tram(const GameObject::BuildParams &params):
	GameObject(params),
	speed(0),
	distanceTraveled(20)
{
}

void Tram::Update()
{
	const float deltaTime = Game::DeltaTime();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		speed += Acceleration() * deltaTime * (1 + glm::pow(1.f - (speed / MAX_SPEED), 4) );
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		speed -= BRAKING_DECELERATION * deltaTime;
	}
	speed -= STATIC_FRICTION_DECELERATION * deltaTime;
	speed -= FRICTION_DECELERATION * (speed / MAX_SPEED) * deltaTime;
	speed = glm::max(speed, 0.f);

	distanceTraveled += speed * deltaTime * SPEED_MULTIPLIER;
	std::cout << "distance traveled: " << distanceTraveled << " speed: " << speed << std::endl;

	auto& track = Game::Resources().GetTrack();
	auto tramAxisPositions = track->GetTramAxisPositions(distanceTraveled, AXIS_DISTANCE);
	const glm::vec3 tramPosition = glm::mix(tramAxisPositions[0], tramAxisPositions[1], 0.5f);
	const float tramYRotation = glm::degrees(Utils::GetYRotation(tramAxisPositions[0] - tramAxisPositions[1]));
	transform.SetLocalPosition(tramPosition);
	transform.SetLocalRotation(180 - tramYRotation, glm::vec3(0, 1, 0));
	CameraPerspective* mainCamera = dynamic_cast<CameraPerspective*>(Game::MainCamera());
	std::cout << "rotation : " << -tramYRotation << std::endl;
	mainCamera->SetYaw(-tramYRotation);
	mainCamera->SetTarget(transform.Position());
}

float Tram::Speed() const
{
	return speed * SPEED_MULTIPLIER;
}

float Tram::DistanceTraveled() const
{
	return distanceTraveled;
}

float Tram::Acceleration()
{
	return ACCELERATION * (0.5 + 0.5*(1 - (speed / MAX_SPEED)));
}
