#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window/Keyboard.hpp>
#include "../Engine/GameObject.h"
#include "Game.h"

class Tram : public GameObject
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
	explicit Tram(const GameObject::BuildParams &params);

	void Update() override;

	float DistanceTraveled() const;

private:
	float Acceleration();

};
