#include "Tram.h"
#include "Game.h"
#include "Track.h"

const float Tram::ACCELERATION = 5;
const float Tram::MAX_SPEED = 50;
const float Tram::BRAKING_DECELERATION = 8;
const float Tram::STATIC_FRICTION_DECELERATION = 3;
const float Tram::FRICTION_DECELERATION = 2;
const float Tram::AXIS_DISTANCE = 8;
const float Tram::SPEED_MULTIPLIER = 1;
const float Tram::TURN_FRICTION_COEFF = 0.002;
const float Tram::GRAVITY_CENTER_ANGLE = 40;
const float Tram::MOMENT_OF_INERTIA = 15;
const float Tram::MASS = 90;
const float Tram::GRAVITY = 9.8;
const float Tram::ANGULAR_DRAG = 0.8;


Tram::Tram(const GameObject::BuildParams &params):
	GameObject(params),
	speed(0),
	distanceTraveled(20)
{
}

void Tram::Initialize()
{
	track = Game::Resources().GetTrack().get();
}

void Tram::Update()
{
	const float deltaTime = Game::DeltaTime(); 
	
	float tramAngularVelocity = track->GetAngularVelocityAtDistance(distanceTraveled);
	centrifugalForce = tramAngularVelocity * speed * speed;
	//std::cout << "centrifugalForce: " << centrifugalForce << std::endl;

	float currentGravityCenterAngle = GRAVITY_CENTER_ANGLE - glm::abs(superAngle);
	float gravityTorque = MASS * GRAVITY * glm::sin(glm::radians(currentGravityCenterAngle));
	if (superAngle == 0) gravityTorque = 0;
	else if (superAngle < 0) gravityTorque *= -1;
	float centrifugalTorque = 2 * centrifugalForce * glm::cos(glm::radians(currentGravityCenterAngle));
	//std::cout << "gravityTorque: " << gravityTorque << "    centrifugalTorque: " << centrifugalTorque << std::endl;
	rolloverTorque = centrifugalTorque - gravityTorque;
	if(superAngle > 0 && rolloverTorque < 0) rolloverTorque *= 7;
	if (superAngle < 0 && rolloverTorque > 0) rolloverTorque *= 7;

	angularAcceleration = rolloverTorque / MOMENT_OF_INERTIA;
	angularVelocity += angularAcceleration * deltaTime;
	angularVelocity = Utils::SmoothStep(angularVelocity, 0.f, 1.f - ANGULAR_DRAG, deltaTime);
	superAngle += angularVelocity * deltaTime;
	superAngle = glm::clamp(superAngle, -89.f, 89.f);
	if (superAngle == 0 || superAngle == 89.f) angularVelocity = 0;
	//std::cout << "angularAcceleration: "<< angularAcceleration << "    angularVelocity: " << angularVelocity << "    superAngle: " << superAngle << std::endl;

	

	UpdateSpeed(deltaTime);

	distanceTraveled += speed * deltaTime * SPEED_MULTIPLIER;

	auto tramAxisPositions = track->GetTramAxisPositions(distanceTraveled, AXIS_DISTANCE);
	const glm::vec3 tramPosition = glm::mix(tramAxisPositions[0], tramAxisPositions[1], 0.5f);
	const float tramYRotation = glm::degrees(Utils::GetYRotation(tramAxisPositions[0] - tramAxisPositions[1]));

	

	transform.SetLocalRotation(superAngle, glm::vec3(0, 0, -1));
	transform.SetLocalPosition(tramPosition);
	//transform.Rotate(90, glm::vec3(0, 1, 0));
	transform.Rotate(180 - tramYRotation, glm::vec3(0, 1, 0));
	//glm::mat4 directionTrans = glm::rotate(glm::mat4(), glm::radians(tramYRotation), glm::vec3(0, 1, 0));
	//glm::vec4 directionV = directionTrans * glm::vec4(0, 0, -1, 1);
	//Utils::DisplayVec3(glm::vec3(directionV));

	CameraPerspective* mainCamera = dynamic_cast<CameraPerspective*>(Game::MainCamera());
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

float Tram::Acceleration() const
{
	return ACCELERATION * (0.5 + 0.5*(1 - (speed / MAX_SPEED)));
}

float Tram::CentrifugalForce() const
{
	return centrifugalForce;
}

void Tram::UpdateSpeed(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		speed += Acceleration() * deltaTime * (1 + glm::pow(1.f - (speed / MAX_SPEED), 4));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		speed -= BRAKING_DECELERATION * deltaTime;
	}
	speed -= STATIC_FRICTION_DECELERATION * deltaTime;
	speed -= FRICTION_DECELERATION * (speed / MAX_SPEED) * deltaTime;
	speed -= TURN_FRICTION_COEFF * glm::abs(centrifugalForce) * deltaTime;
	//std::cout << "Turn deceleration: " << TURN_FRICTION_COEFF * centrifugalForce * deltaTime << std::endl;
	speed = glm::max(speed, 0.f);
}
