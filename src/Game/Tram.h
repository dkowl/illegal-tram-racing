#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window/Keyboard.hpp>

class Tram
{
public:
	static const float AXIS_DISTANCE;
private:
	static const float ACCELERATION; //		m/s^2
	static const float MAX_SPEED; //		m/s
	static const float FRICTION_DECELERATION;
	static const float BRAKING_DECELERATION;

	float speed;
	float distanceTraveled;

public:
	Tram();

	void Update(float deltaTime);

	float DistanceTraveled() const;

private:
	float Acceleration();

};