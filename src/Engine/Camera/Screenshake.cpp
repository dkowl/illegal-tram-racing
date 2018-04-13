#include <glm/gtc/random.hpp>

#include "Screenshake.h"
#include "Camera.h"
#include "../../Game/Game.h"
#include "../../Game/Tram.h"
#include "../../Utils.h"


Screenshake::Screenshake():
	impactTime(0.1),
	baseImpactForce(10),
	springMass(1),
	impactChancePerSecond(1),
	springCoeff(200),
	dragCoeff(40)
{
	
}

void Screenshake::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void Screenshake::Initialize()
{
	camera = Game::MainCamera();
	tram = Game::I().GetObject<Tram>("Tram");
}

void Screenshake::Update()
{
	const float deltaTime = Game::DeltaTime();
	const float impactChance = impactChancePerSecond * deltaTime;
	const float rand = glm::linearRand(0.f, 1.f);
	if (rand < impactChance) Shake();
	Utils::DisplayVec3(ImpactForce(), "Impact F");
	Utils::DisplayVec3(SpringForce(), "Spring F");
	Utils::DisplayVec3(DragForce(), "Drag F");
	acceleration = (ImpactForce() + SpringForce() + DragForce()) / springMass;
	velocity += acceleration * deltaTime;
	offset += velocity * deltaTime;
	Utils::DisplayVec3(offset, "Offset");
	timeSinceLastImpact += deltaTime;
	camera->SetScreenshakeOffset(offset);
}

glm::vec3 Screenshake::ImpactForce() const
{
	if (timeSinceLastImpact < impactTime)
	{
		return impactDirection * baseImpactForce * tram->Speed();
	}
	else return glm::vec3(0);
}

glm::vec3 Screenshake::SpringForce() const
{
	return offset * springCoeff * -1.f;
}

glm::vec3 Screenshake::DragForce() const
{
	return velocity * glm::length(velocity) * dragCoeff * -1.f;
}

void Screenshake::Shake()
{
	const glm::vec2 rand = glm::circularRand(1.f);
	const glm::vec3 rand3 = glm::vec3(rand.x * 10, rand.y, 0);
	if(glm::length(rand3) != 0) impactDirection = glm::normalize(rand3);
	else impactDirection = glm::vec3(0);
	timeSinceLastImpact = 0;
}
