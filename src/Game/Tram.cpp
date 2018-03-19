#include "Tram.h"

const float Tram::ACCELERATION = 2;
const float Tram::MAX_SPEED = 30;
const float Tram::BRAKING_DECELERATION = 5;
const float Tram::FRICTION_DECELERATION = 1;
const float Tram::AXIS_DISTANCE = 8;


Tram::Tram():
	speed(0),
	distanceTraveled(20)
{
}

void Tram::Update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		speed += Acceleration() * deltaTime;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		speed -= BRAKING_DECELERATION * deltaTime;
	}
	speed -= FRICTION_DECELERATION * (speed / MAX_SPEED)*(speed / MAX_SPEED) * deltaTime;
	speed = glm::max(speed, 0.f);

	distanceTraveled += speed * deltaTime;

	std::cout << "distance traveled: " << distanceTraveled << " speed: " << speed << std::endl;
}

float Tram::DistanceTraveled() const
{
	return distanceTraveled;
}

float Tram::Acceleration()
{
	return ACCELERATION * (0.5 + 0.5*(1 - (speed / MAX_SPEED)));
}
